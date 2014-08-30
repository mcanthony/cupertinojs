/*
<expect>
-32
52
</expect>
*/

function testMinusEqual(){
    var a = 10
    var b = 42
    a -= b
    cujs_log("%@", a);
}

function testPlusEqual(){
    var a = 10
    var b = 42
    a += b
    cujs_log("%@", a);
}

function main(a, b){
    testMinusEqual()
    testPlusEqual()
   
    var zero = 0
    return zero.intValue
}