//
//  main.cpp
//  cujs-compiler-integration-tests
//
//  Created by Jerry Marino on 8/25/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>
#include "dirent.h"
#include "assert.h"
#include "cujsutils.h"

using namespace cujs;

static std::string exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    assert(pipe && "Cannot execute cmd");
    
    char buffer[128];
    std::string result = "";
    
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL){
    		result += buffer;
        }
    }
    
    pclose(pipe);
    return result;
}

struct TestRunOptions {
    std::string testSourceDir;
    std::string cujsCompiler;
    std::string buildDir;
    std::string focusedTest;
};

class TestRun {
    TestRunOptions _options;
    std::string _path;

    bool assertOutputMatchesExpectation(std::string output){
        auto fullPath = string_format("%s/%s",
                                      _options.testSourceDir.c_str(),
                                      _path.c_str());
        
        auto file = getFileContents(fullPath.c_str());
        auto expectation = expectationInFile(file);
        
        bool didMatch = output == expectation;
        if (!didMatch) {
            std::cout << "Expected output:\n" << expectation << "\n";
            std::cout << "Actual output:\n" << output << "\n";
        }
        
        return didMatch;
    }
    
    std::string getFileContents(const char *filename){
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        assert(in);
        return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
    }
    
    // match everything between <expect>\n and \n</expect>
    std::string expectationInFile(std::string file){
        std::cmatch startMatch;
        std::regex_search(file.c_str(),
                          startMatch,
                          std::regex("<expect\\>\\n"));
        auto suffix = startMatch.suffix();
        
        if (suffix.length()) {
            auto endFile = std::string(suffix.str());
            std::cmatch endMatch;
            std::regex_search(endFile.c_str(),
                              endMatch,
                              std::regex("(\\(|\\)|\\[|\\]|\\\"|\\.|:|\\d|\\w|\\s)*+\\<\\/expect"));
            
            auto expectation = std::string(endMatch[0]);
            return expectation;
        }
        
        return std::string();
    }

public:
    TestRun(std::string path, TestRunOptions options){
        _options = options;
        _path = path;
    }
    
    bool run(){
        std::cout << "Running test " << _path << "\n";
        auto compileCommand = string_format("%s %s/%s 2>&1",
                                            _options.cujsCompiler.c_str(),
                                            _options.testSourceDir.c_str(),
                                            _path.c_str());
        
        auto compilationResult = exec(compileCommand.c_str());
        
        std::cout << "Complation:\n" << compilationResult << "\n";
        
        auto runTestProgramCommand = string_format("%s/cujsapp 2>&1", _options.buildDir.c_str());
        auto testProgramResult = exec(runTestProgramCommand.c_str());
        
        bool didMatch = assertOutputMatchesExpectation(testProgramResult);
        return didMatch;
    }
};

bool fileIsTest(std::string file){
    return file.find("test") == 0 && file.find(".js") == file.length() - 3;
}

std::vector <std::string>testFilesForOptions(TestRunOptions options){
    std::vector <std::string>tests;
    if (options.focusedTest.length()) {
        assert(fileIsTest(options.focusedTest) && "Invalid test");
        tests.push_back(options.focusedTest);
        return tests;
    }
    
    DIR *sourceDir = opendir(options.testSourceDir.c_str());
    assert(sourceDir && "Missing test directory");
   
    struct dirent *entry;
    while ((entry = readdir(sourceDir))) {
        std::string file = std::string(entry->d_name);
        if (fileIsTest(file)) {
            tests.push_back(file);
        }
    }
    
    closedir(sourceDir);  
    return tests;
}

int main(int argc, const char * argv[])
{
    //Run OSX integration tests
    TestRunOptions options;
    options.buildDir = "/tmp/cujs-integration-tests";
    options.testSourceDir = string_format("%s/test-js", PROJECT_DIR);
    options.cujsCompiler = "/usr/local/bin/cujs";
    options.focusedTest = get_env_var("CUJS_FOCUSED_TEST");
    
    setenv("CUJS_ENV_RUNTIME", "/usr/local/lib/libcujs-runtime.a", 0);
    setenv("CUJS_ENV_CREATE_EXECUTABLE", "true", 0);
    setenv("CUJS_ENV_BUILD_DIR", options.buildDir.c_str(), 0);
    setenv("CUJS_ENV_PROJECT_ROOT_DIR", options.testSourceDir.c_str(), 0);
   
    std::cout << "Welcome to Cupertino.js! \n\n";
    std::cout << "Starting test run.. \n\n";
    
    exec(string_format("mkdir -p %s", options.buildDir.c_str()).c_str());
  
    auto testFiles = testFilesForOptions(options);
    std::vector<std::string>failedTests;
    auto testCount = testFiles.size();
    for (unsigned i = 0; i < testCount; i++) {
        auto testFile = testFiles[i];
        TestRun testRun(testFile, options);
        bool status = testRun.run();
        if (!status) {
            failedTests.push_back(testFile);
        }
    }
    
    std::cout << "\n\n--------------------------------\n";
    auto failedCount = failedTests.size();
    std::cout << "Passed " << testCount - failedCount << " out of " << testCount << " tests\n\n";
   
    if (failedCount) {
        std::cout << "Failures: \n";
        for (auto i = 0; i < failedTests.size(); i++){
            std::cout << failedTests[i] << "\n";
        }
    }
    
    std::cout << "--------------------------------\n";
    return 0;
}
