/*
<expect>
for: 0
for: 1
for: 2
for: 3
for: 4
for: 5
after: 5
</expect>
*/

function testForBreak(){
    var i;
    for (i = 0; i < 10; i = i + 1){
        cujs_log("for: %@", i);
        if (i == 5)
            break
    }
    
    cujs_log("after: %@", i);
}

function main(a, b){
    testForBreak()
    
    var zero = 0
    return zero.intValue
}