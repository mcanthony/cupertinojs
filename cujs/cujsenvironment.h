//
//  cujsenvironment.h
//  cujs
//
//  Created by Jerry Marino on 9/2/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#ifndef __cujs__cujsenvironment__
#define __cujs__cujsenvironment__

#include <iostream>

const extern char *COMPILE_ENV_BUILD_DIR;
const extern char *COMPILE_ENV_CUJS_RUNTIME_PATH;
const extern char *COMPILE_ENV_DEBUG;
const extern char *COMPILE_ENV_CREATE_EXECUTABLE;
const extern char *COMPILE_ENV_MTRIPEL;
const extern char *COMPILE_ENV_SDKROOT;
const extern char *COMPILE_ENV_PLATFORM_NAME;
const extern char *COMPILE_ENV_ARCHS;

bool CUJSIsIOS();

#endif /* defined(__cujs__cujsenvironment__) */
