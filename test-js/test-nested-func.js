/*
<expect>
walks up
bullit burbon old fashioned maam
ordered 1 cocktail: 42
sips drink
</expect>
*/

function orderCocktail(argument){
    cujs_log("bullit burbon old fashioned maam")
    
    function oldFashion(){
        return 42
    }
    return oldFashion()
}

function testNestedFunction(){
    cujs_log("walks up")
    cujs_log("ordered 1 cocktail: %@", orderCocktail(1))
    cujs_log("sips drink")
}

function main(a, b){
    testNestedFunction()
    
    var zero = 0
    return zero.intValue
}
