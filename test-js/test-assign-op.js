/*
<expect>
-32
52
</expect>
*/

function testMinusEqual(){
    var a = 10
    var b = 42
    var result = a -= b
    cujs_log("%@", result);
}

function testPlusEqual(){
    var a = 10
    var b = 42
    var result = a += b
    cujs_log("%@", result);
}

function main(_a, _b){
    testMinusEqual()
    testPlusEqual()
    
    var zero = 0
    return zero.intValue
}