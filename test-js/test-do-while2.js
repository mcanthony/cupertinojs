/*
<expect>
while: 1
while: 2
while: 3
while: 4
while: 6
while: 7
while: 8
while: 9
while: 10
after: 10
</expect>
*/

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

function main(a, b){
    testDoWhileBreak()
    
    var zero = 0
    return zero.intValue
}