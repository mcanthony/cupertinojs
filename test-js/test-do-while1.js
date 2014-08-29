/*
<expect>
while: 1
while: 2
while: 3
while: 4
while: 5
while: 6
while: 7
while: 8
while: 9
while: 10
after: 10
</expect>
*/

function testDoWhile(){
    var j = 0;
    do {
        j = j + 1
        cujs_log("while: %@", j);
    } while (j < 10)

    cujs_log("after: %@", j);
}

function main(a, b){
    testDoWhile()
    
    var zero = 0
    return zero.intValue
}