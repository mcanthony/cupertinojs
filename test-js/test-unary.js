/*
<expect>
1
1
1
</expect>
*/

function logNot(a){
    cujs_log("%@", !!!a)
}

function logNotEqual(a){
    cujs_log("%@", a != 1)
}

function logNotEqualStrict(a){
    cujs_log("%@", a !== 1)
}

function testEq(){
    logNot(0)
    logNotEqual(0)
    logNotEqualStrict(0)
}

function main(a, b){
    testEq()
    
    var zero = 0
    return zero.intValue
}