/*
<expect>
Drink
Drink
</expect>
*/

function Drink(){}

function testVariablesAsReferencesToFunctionObjectsAreTheSame(){
    var Bullit = Drink
    var drink  = new Bullit()
    cujs_log("%@", drink.class)
    cujs_log("%@", Bullit)
}

function main(a, b){
    testVariablesAsReferencesToFunctionObjectsAreTheSame()
    
    var zero = 0
    return zero.intValue
}