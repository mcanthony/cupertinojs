/*
<expect>
apples
banannas
</expect>
*/

function testArrayCreationSubscripting(){
    var fruits = ["apples", "banannas"]
    cujs_log("%@", fruits[0])
    cujs_log("%@", fruits[1])
}

function main(a, b){
    testArrayCreationSubscripting()

    var zero = 0
    return zero.intValue
}
