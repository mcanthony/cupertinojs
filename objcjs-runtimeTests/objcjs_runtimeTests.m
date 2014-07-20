//
//  objcjs_runtimeTests.m
//  objcjs-runtimeTests
//
//  Created by Jerry Marino on 7/15/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "objcjs_runtime.h"

@interface objcjs_runtimeTests : XCTestCase

@end

@implementation objcjs_runtimeTests

static BOOL calledBody;

- (void)setUp
{
    [super setUp];
    calledBody = NO;
}

- (void)tearDown
{
    [super tearDown];
}

id impl1(id firstObject, ...){
    calledBody = YES;

    va_list argumentList;
    va_start(argumentList, firstObject);
    id instance = firstObject;
    NSLog(@"%@", instance);
   
    SEL selector = va_arg(argumentList, SEL);
    NSLog(@"%s", sel_getName(selector));
    
    id firstVArgument = va_arg(argumentList, id);
    NSLog(@"%@", firstVArgument);
    va_end(argumentList);
    return firstVArgument;
}

//id impl2(id firstObject, void *second, void *third, ...){
//    calledBody = YES;
//    
//    va_list argumentList;
//    va_start(argumentList, firstObject);
//    id instance = firstObject;
//    NSLog(@"%@", instance);
//    
//    SEL selector = va_arg(argumentList, SEL);
//    NSLog(@"%s", sel_getName(selector));
//    
//    id arg3 = va_arg(argumentList, id);
//    NSLog(@"%@", arg3);
//    va_end(argumentList);
//    return arg3;
//}

- (void)testItCanCreateASubclass
{
    defineJSFunction("subclass-1", impl1);
    Class aClass = objc_getClass("subclass-1");
    JSFunction *f = [aClass new];
    id result = [f body:@"An Arg"];
    
    XCTAssertTrue(f, @"It creates a subclass");
    XCTAssertTrue(calledBody, @"It creates a subclass");
   
    //TODO : test the impl of body
    XCTAssertEqual(@"An Arg", result, @"It returns the arg");
}

- (void)testItCanDefineAPropety{
    const char *name = "name";
    JSFunction *f = [JSFunction new];
    [f defineProperty:name];
    XCTAssertTrue([f respondsToSelector:NSSelectorFromString(@"name")], @"It adds a getter");
    XCTAssertTrue([f respondsToSelector:NSSelectorFromString(@"setName:")], @"It adds a setter");
    
    [f performSelector:NSSelectorFromString(@"setName:") withObject:@3];
    id nameValue = [f performSelector:NSSelectorFromString(@"name")];
    XCTAssertEqual(nameValue, @3, @"It can set the value");
}

- (void)testItCanSetAParent {
    JSFunction *parent = [JSFunction new];
    defineJSFunction("child", impl1);
    Class childClass = objc_getClass("child");
    [childClass setParent:parent];
    XCTAssertEqual([childClass parent], parent, @"It has a parent");
}

- (void)testItCanInvokeAJSFunctionInstance {
    defineJSFunction("subclass-2", impl1);
    Class aClass = objc_getClass("subclass-1");
    JSFunction *f = [aClass new];
    id result = objcjs_invoke(f, CFRetain(@"An Arg"));
    
    XCTAssertTrue(calledBody, @"It invokes body:");
    XCTAssertEqual(@"An Arg", result, @"It returns the arg");
}

- (void)testItCanInvokeAJSFunction {
    defineJSFunction("subclass-3", impl1);
    Class aClass = objc_getClass("subclass-3");
   
    id result = objcjs_invoke(aClass, CFRetain(@"An Arg"));
    XCTAssertTrue(calledBody, @"It invokes body: on a new instance");
    XCTAssertEqual(@"An Arg", result, @"It returns the arg");
}

@end