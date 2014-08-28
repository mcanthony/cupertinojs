/*
<expect>
1337
42
</expect>
*/

function conditional(condition){
    var a
    if (condition){
        a = 1337
    } else {
        a = 42
    }
    return a
}

function testConditionalWithReturn(){
    cujs_log("%@", conditional(1))
    cujs_log("%@", conditional(0))
}

function conditional2(condition){
    if (condition){
        return 1337;
    } else {
        return 42;
    }
    return 666;
}

function testConditionalWithLastStatementReturn(){
    cujs_log("%@", conditional2(1))
    cujs_log("%@", conditional2(0))
}

function main(a, b){
//FIXME: once worked
//    testConditionalWithReturn()
    
    testConditionalWithLastStatementReturn()

    var zero = 0
    return zero.intValue
}
