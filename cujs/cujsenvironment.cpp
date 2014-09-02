//
//  cujsenvironment.cpp
//  cujs
//
//  Created by Jerry Marino on 9/2/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#include "cujsenvironment.h"
#include "cujsutils.h"

const char *COMPILE_ENV_BUILD_DIR = "CUJS_ENV_BUILD_DIR";
const char *COMPILE_ENV_CUJS_RUNTIME_PATH = "CUJS_ENV_RUNTIME";
const char *COMPILE_ENV_DEBUG = "CUJS_ENV_DEBUG_COMPILER";
const char *COMPILE_ENV_CREATE_EXECUTABLE = "CUJS_ENV_CREATE_EXECUTABLE";
const char *COMPILE_ENV_MTRIPEL = "CUJS_ENV_MTRIPEL";
const char *COMPILE_ENV_SDKROOT = "SDKROOT";
const char *COMPILE_ENV_PLATFORM_NAME = "PLATFORM_NAME";
const char *COMPILE_ENV_ARCHS = "ARCHS";


using namespace cujs;

bool CUJSIsIOS(){
    auto platformName = get_env_var(COMPILE_ENV_PLATFORM_NAME);
    return (platformName == "iphonesimulator");
};
