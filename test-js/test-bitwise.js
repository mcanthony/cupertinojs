/*
<expect>
bitor 42
testBitXOr 32
testBitAnd 10
testBitShiftLeft 10240
bitShiftRight 0
bitShiftRightRight 5
assignBitShiftRightRight 5
</expect>
*/

function testBitOr(){
    var a = 10
    var b = 42
    cujs_log("bitor %@", a | b)
}

function testBitXOr(){
    var a = 10
    var b = 42
    cujs_log("testBitXOr %@",  a ^ b)
}

function testBitAnd(){
    var a = 10
    var b = 42
    cujs_log("testBitAnd %@", a & b)
}

function testBitShiftLeft(){
    var a = 10
    var b = 42
    cujs_log("testBitShiftLeft %@", a << b)
}

function testBitShiftRight(){
    var a = 10
    var b = 42
    cujs_log("bitShiftRight %@", a >> b)
}

function testBitShiftRightRight(){
    var a = 10
    var b = 1
    cujs_log("bitShiftRightRight %@", a >>> b)
}

function testAssignBitShiftRightRight(){
    var a = 10
    var b = 1
    a >>>= b
    cujs_log("assignBitShiftRightRight %@", a)
}

function main(a, b){
    testBitOr()
    testBitXOr()
    testBitAnd()
    testBitShiftLeft()
    testBitShiftRight()
    testBitShiftRightRight()
    testAssignBitShiftRightRight()
    
    var zero = 0
    return zero.intValue
}
