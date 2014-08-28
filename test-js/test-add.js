/*
<expect>
4
5
</expect>
*/

function add(x, y){
    return x + y;
}

function testAddNumericParams(){
    cujs_log("%@", add(1,3))
}

function add1(x, y){
    return x + y + 1;
}

function testAddNumericParamsWithNumberLiteral(){
    cujs_log("%@", add1(1,3))
}

function main(a,b){
    testAddNumericParams()
    testAddNumericParamsWithNumberLiteral()
    
    var zero = 0
    return zero.intValue
}
