//
//  test-compiler.cpp
//  cujs
//
//  Created by Jerry Marino on 9/2/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <include/libplatform/libplatform.h>
#include <src/isolate.h>
#include "cujscompiler.h"

using namespace cujs;

TEST(CompilerOptionsMTripelSim, Positive){
    setenv("SDKROOT", "/anSDK", 0);
    setenv("ARCHS", "i386", 0);
    setenv("PLATFORM_NAME", "iphonesimulator", 0);
    CompilerOptions options(0, NULL);
    EXPECT_EQ(options._mTripel, "i386-apple-ios");
}

TEST(CompilerOptionsMTripelDefault, Positive){
    unsetenv("SDKROOT");
    unsetenv("ARCHS");
    unsetenv("PLATFORM_NAME");
    CompilerOptions options(0, NULL);
    EXPECT_THAT(std::string(""), testing::StrEq(options._mTripel.c_str()));
}