/*
<expect>
1
1
0
0
0
0
</expect>
*/

function logLessThan(a){
    cujs_log("%@", a < 1)
}

function logLessThanOrEqual(a){
    cujs_log("%@", a <= 1)
}

function logGreaterThanOrEqual(a){
    cujs_log("%@", a >= 1)
}

function logGreaterThan(a){
    cujs_log("%@", a > 1)
}

function logEqualStrict(a){
    cujs_log("%@", a === 1)
}

function logEqual(a){
    cujs_log("%@", a == 1)
}

function testEq(){
    logLessThan(0)
    logLessThanOrEqual(0)
    logGreaterThan(0)
    logGreaterThanOrEqual(0)
    logEqualStrict(0)
    logEqual(0)
}

function main(a, b){
    testEq()
    
    var zero = 0
    return zero.intValue
}
