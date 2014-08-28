/*
<expect>
//FIXME: once worked
</expect>
*/

function testPlusEqual(a, b){
    var a = 10
    var b = 42
    var result = a -= b
    cujs_log("%@", result);
}

function testMinusEqual(){
    var a = 10
    var b = 42
    var result = a -= b
    cujs_log("%@", result);
}

function main(a, b){
    testPlusEqual()
    testMinusEqual()
   
    var zero = 0
    return zero.intValue
}