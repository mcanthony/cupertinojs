/*
<expect>
the output must match
what lies between expect
and is limited to digits
letters [ ] . ( ) and :
</expect>
*/

function testLogging(){
    cujs_log("the output must match")
    cujs_log("what lies between expect")
    cujs_log("and is limited to digits")
    cujs_log("letters [ ] . ( ) and :")
}

function main(a,b){
    testLogging()
    
    var zero = 0
    return zero.intValue
}