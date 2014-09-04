//
//  cujscompiler.cpp
//  cujs
//
//  Created by Jerry Marino on 7/26/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#include <assert.h>
#include <vector>
#include <iostream>
#include <fstream>

#include <src/parser.h>
#include <src/prettyprinter.h>
#include <tools/shell-utils.h>
#include <include/libplatform/libplatform.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Bitcode/ReaderWriter.h>

#include "cujsutils.h"
#include "cgjs.h"
#include "cujsenvironment.h"

#include "cujscompiler.h"

using namespace v8::internal;
using namespace cujs;

const char *LLVM_DYLIB_PATH = "/usr/local/lib/cujs-deps";
const char *LLVM_BIN_PATH = "/usr/local/bin/cujs-deps";

#pragma mark - CompilerOptions

std::vector<std::string> ParseNames(int argc, const char * argv[]){
    std::vector<std::string> fnames;
    std::string benchmark;
    int repeat = 1;
    Encoding encoding = LATIN1;
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--latin1") == 0) {
            encoding = LATIN1;
        } else if (strcmp(argv[i], "--utf8") == 0) {
            encoding = UTF8;
        } else if (strcmp(argv[i], "--utf16") == 0) {
            encoding = UTF16;
        } else if (strncmp(argv[i], "--benchmark=", 12) == 0) {
            benchmark = std::string(argv[i]).substr(12);
        } else if (strncmp(argv[i], "--repeat=", 9) == 0) {
            std::string repeat_str = std::string(argv[i]).substr(9);
            repeat = atoi(repeat_str.c_str());
        } else if (i > 0 && argv[i][0] != '-') {
            fnames.push_back(std::string(argv[i]));
        }
    }
    return fnames;
}

std::string GetMTriple(){
    auto explicitTriple = get_env_var(COMPILE_ENV_MTRIPEL);
    if (explicitTriple.length()) {
        return explicitTriple;
    }
   
    auto platformName = get_env_var(COMPILE_ENV_PLATFORM_NAME);
    auto archs = get_env_var(COMPILE_ENV_ARCHS);

    if (archs.length() && platformName.length()) {
        auto osName = CUJSIsIOS() ? "ios" : "osx";
        return string_format("%s-apple-%s", archs.c_str(), osName);
    }
   
    return "";
}

cujs::CompilerOptions::CompilerOptions(int argc, const char * argv[]){
    _names = ParseNames(argc, argv);
    _runtimePath = get_env_var(COMPILE_ENV_CUJS_RUNTIME_PATH);
    _buildDir = get_env_var(COMPILE_ENV_BUILD_DIR);
    _debug = get_env_var(COMPILE_ENV_DEBUG) == "true";
    _createExecutable = get_env_var(COMPILE_ENV_CREATE_EXECUTABLE) == "true";
    _mTripel = GetMTriple();
}

int cujs::CompilerOptions::validate(){
    if(!_names.size()){
        std::cout << "no input files \n";
        return 0;
    }
    
    if(!_buildDir.length()){
        std::cout << "missing build dir \n";
        return 0;
    }
    
    return 1;
}

#pragma mark - Compiler

cujs::Compiler::Compiler(CompilerOptions options, v8::Isolate *isolate){
    _options = &options;
    _isolate = isolate;
}


class StringResource8 : public v8::String::ExternalAsciiStringResource {
public:
    StringResource8(const char* data, int length)
    : data_(data), length_(length) { }
    virtual size_t length() const { return length_; }
    virtual const char* data() const { return data_; }
    
private:
    const char* data_;
    int length_;
};

v8::Handle<v8::String>SourceHandleWithName(const char *sourceName, v8::Isolate *isolate){
    int length = 0;
    const byte* source = ReadFileAndRepeat(sourceName, &length, 1);
    
    v8::Handle<v8::String> source_handle;
    Encoding encoding = LATIN1;
    
    switch (encoding) {
        case UTF8: {
            source_handle = v8::String::NewFromUtf8(
                                                    isolate, reinterpret_cast<const char*>(source));
            break;
        }
        case UTF16: {
            source_handle = v8::String::NewFromTwoByte(
                                                       isolate, reinterpret_cast<const uint16_t*>(source),
                                                       v8::String::kNormalString, length / 2);
            break;
        }
        case LATIN1: {
            StringResource8* string_resource;
            string_resource =
            new StringResource8(reinterpret_cast<const char*>(source), length);
            source_handle = v8::String::NewExternal(isolate, string_resource);
            
            break;
        }
    }
    return source_handle;
}

CompilationInfoWithZone *ProgramWithSourceHandle(v8::Handle<v8::String> source_handle, cujs::CompilerOptions options){
    
    v8::base::TimeDelta parse_time1, parse_time2;
    Handle<String> handle = v8::Utils::OpenHandle(*source_handle);
    Handle<Script> script = Isolate::Current()->factory()->NewScript(handle);
    
    // First round of parsing (produce data to cache).
    auto info = new CompilationInfoWithZone(script);
    info->MarkAsGlobal();
    info->MarkNonOptimizable();
    info->MarkAsEval();
    assert(!info->is_lazy());
    
    bool success = Parser::Parse(info, false);
    if (!success) {
        fprintf(stderr, "Parsing failed\n");
        abort();
    }
#if DEBUG
    if (options._debug) {
        PrintF(AstPrinter(info->zone()).PrintProgram(info->function()));
    }
#endif
    
    return info;
}

std::string CompileBitcodeCommandForOptionsFile(CompilerOptions options, std::string outFileName){
 
    std::string compileCMD = "LD_LIBRARY_PATH=";
    compileCMD += LLVM_DYLIB_PATH;
    compileCMD += " ";
    compileCMD += LLVM_BIN_PATH;
    compileCMD += "/llc ";
    if (options._mTripel.length()) {
        compileCMD += "-mtriple ";
        compileCMD += options._mTripel;
    }
    
    compileCMD += " ";
    compileCMD += outFileName;
    return compileCMD;
}

std::string BitcodeWithModule(llvm::Module *module){
    llvm::verifyModule(*module, llvm::PrintMessageAction);
    llvm::PassManager PM;
    std::string error;
    std::string out;
    
    llvm::raw_string_ostream file(out);
    PM.add(createPrintModulePass(&file));
    PM.run(*module);
    return out;
}

void WriteBitcodeToFile(std::string bitcode, std::string outFileName){
    std::ofstream outfile;
    outfile.open(outFileName);
    outfile << bitcode;
    outfile.close();
}

std::string cujs::Compiler::compileModule(v8::Isolate *isolate, std::string filePath){
    std::string buildDir = get_env_var(COMPILE_ENV_BUILD_DIR);
    std::string fileName = split(filePath, '/').back();
    std::string moduleName = split(fileName, '.').front();
    
    assert(moduleName.length() && "missing file");
    
    auto module = ProgramWithSourceHandle(SourceHandleWithName(filePath.c_str(), isolate), *_options);
    
    CGJS codegen = CGJS(moduleName, module);
    codegen.Codegen();
    if (_options->_debug) {
        codegen.Dump();
    }
   
    std::string outFileName = string_format("%s/%s.bc", buildDir.c_str(), moduleName.c_str());
   
    auto bitcode = BitcodeWithModule(codegen.module());
    WriteBitcodeToFile(bitcode, outFileName);
    system(CompileBitcodeCommandForOptionsFile(*_options, outFileName).c_str());
    std::string llcOutput = string_format("%s/%s.s", buildDir.c_str(), moduleName.c_str());
    return llcOutput;
}

void cujs::Compiler::run(){
    std::string sFiles;
    CompilerOptions options = *_options;
    for (unsigned i = 0; i < options._names.size(); i++){
        std::string filePath = options._names[i];
        std::string sFile = compileModule(_isolate, filePath);
        sFiles += " ";
        sFiles += sFile;
    }

    if (options._createExecutable){
        std::string clangCmd = string_format("LD_LIBRARY_PATH=%s %s/clang -framework Foundation %s %s -o %s/cujsapp",
                                             LLVM_DYLIB_PATH,
                                             LLVM_BIN_PATH,
                                             options._runtimePath.c_str(),
                                             sFiles.c_str(),
                                             options._buildDir.c_str());
        system(clangCmd.c_str());
    }
}
