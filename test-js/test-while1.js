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

function testWhile(){
    var j = 0;
    while (j < 10) {
        j = j + 1
        cujs_log("while: %@", j);
    }

    cujs_log("after: %@", j);
}

function main(a, b){
    testWhile()
    
    var zero = 0
    return zero.intValue
}