/*
<expect>
bullit burbon
</expect>
*/

function testRemovingBasicBlocks(){
    var boozey = true
    cujs_log("bullit burbon")
    return
    
    if (1 < 2){
        cujs_log("fail")
    }
}

function main(a,b){
    testRemovingBasicBlocks()
    var zero = 0
    return zero.intValue
}