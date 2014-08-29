/*
<expect>
for: 0
for: 1
for: 2
for: 3
for: 4
for: 5
for: 6
for: 7
for: 8
for: 9
after: 10
</expect>
*/

function testFor(){
    for (var i = 0; i < 10; i = i + 1){
        cujs_log("for: %@", i);
    }

    cujs_log("after: %@", i);
}

function main(a, b){
    testFor()
    
    var zero = 0
    return zero.intValue
}

