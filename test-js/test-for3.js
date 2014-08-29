/*
<expect>
for: 0
for: 1
for: 2
for: 3
for: 4
for: 6
for: 7
for: 8
for: 9
</expect>
*/

function testForContinue(){
    for (var i = 0; i < 10; i = i + 1){
        if (i == 5)
            continue
        cujs_log("for: %@", i);
    }
}

function main(a, b){
    testForContinue()
    
    var zero = 0
    return zero.intValue
}