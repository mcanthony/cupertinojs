//
//  test-cgclang.cpp
//  cujs
//
//  Created by Jerry Marino on 9/1/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cgclang.h"

using namespace cujs;

TEST(TranslationUnitOptionsFilePathStartsAtRoot, Positive) {
    setenv("CUJS_ENV_PROJECT_ROOT_DIR", "root", 0);
    TranslationUnitOptions options = TranslationUnitOptions::OptionsWithFile("header.h");
    EXPECT_EQ(options.file, "root/header.h");
}

TEST(TranslationUnitOptionsArgsContainsSDK, Positive){
    setenv("SDKROOT", "/anSDK", 0);
    TranslationUnitOptions options = TranslationUnitOptions::OptionsWithFile("header.h");
    EXPECT_THAT(options.args, testing::Contains(testing::StrEq("-isysroot/anSDK")));
}

TEST(TranslationUnitOptionsArgsContainsArch, Positive){
    setenv("ARCHS", "i386", 0);
    TranslationUnitOptions options = TranslationUnitOptions::OptionsWithFile("header.h");
    EXPECT_THAT(options.args, testing::Contains(testing::StrEq("i386")));
}
