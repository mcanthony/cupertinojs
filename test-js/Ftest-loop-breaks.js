/*
<expect>
//FIXME: once worked
this likely broken by the commit that
'cleaned up after basic blocks'
broken tests should not be added to repo bu this used to work
so make the exception
</expect>
*/

function testForBreak(){
    for (var i = 0; i < 10; i = i + 1){
        if (i == 5)
            break
        
        cujs_log("for: %@", i);
    }

    cujs_log("after: %@", i);
}

function testForContinue(){
    for (var i = 0; i < 10; i = i + 1){
        if (i == 5)
            continue
        
        cujs_log("for: %@", i);
    }

    cujs_log("after: %@", i);
}

function testWhileBreak(){
    var j = 0;
    while (j < 10) {
        j = j + 1
        if (j == 5)
            break
            
        cujs_log("do: %@", j);
    }
    
    cujs_log("after: %@", j);
}

function testWhileContinue(){
    var j = 0;
    while (j < 10) {
        j = j + 1
        if (j == 5)
            continue
            
        cujs_log("while: %@", j);
    }
    
    cujs_log("after: %@", j);
}

function testDoWhileBreak(){
    var j = 0;
    do {
        j = j + 1
        if (j == 5)
            continue
            
        cujs_log("while: %@", j);
    } while (j < 10)
    
    cujs_log("after: %@", j);
}

function testDoWhileContinue(){
    var j = 0;
    do {
        j = j + 1
        if (j == 5)
            continue
            
        cujs_log("do: %@", j);
    } while (j < 10)
    
    cujs_log("after: %@", j);
}

function main(a, b){
    testForBreak()
    testForContinue()
    testDoWhileBreak()
    testDoWhileContinue()
    testWhileBreak()
    testWhileContinue()

    var zero = 0
    return zero.intValue
}
