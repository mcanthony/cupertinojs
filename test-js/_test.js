// _test.js - used to manually test features
// with test-js/Makefile or in xcode with scheme
// FIXME: this scheme should be renamed
// cujs-compile-test

function sayHello(){
    cujs_log("hello world")
}

// actual system main definition
//
// it must return an integer exit code
// and since numbers are objects in JS
// you need to return the int value of the object
function main(a,b){
    sayHello()
    
    var zero = 0
    return zero.intValue
}