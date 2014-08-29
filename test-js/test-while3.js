/*
<expect>
while: 1
while: 2
while: 3
while: 4
after: 5
</expect>
*/

function testWhileBreak(){
    var j = 0;
    while (j < 10) {
        j = j + 1
        if (j == 5)
            break
        cujs_log("while: %@", j);
    }
    
    cujs_log("after: %@", j);
}

function main(a, b){
    testWhileBreak()
    
    var zero = 0
    return zero.intValue
}