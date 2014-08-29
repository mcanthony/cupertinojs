/*
<expect>
do: 1
do: 2
do: 3
do: 4
do: 6
do: 7
do: 8
do: 9
do: 10
after: 10
</expect>
*/

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
    testDoWhileContinue()
    
    var zero = 0
    return zero.intValue
}