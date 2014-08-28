/*
<expect>
started with 0
counter: nested
one: 1
two: 2
three: 3
four: 4
</expect>
*/

function Counter(start){
    cujs_log("started with %@", start);

    var count = start
    
    function nested(){
        
        function doubleNested(){
            count = count + 1
            return count;
        }
        
        return doubleNested();
    }
    
    return nested
}

function testClosures(){
    var counter = Counter(0);
    
    cujs_log("counter: %@", counter);
    cujs_log("one: %@", counter())
    cujs_log("two: %@", counter())
    cujs_log("three: %@", counter())
    cujs_log("four: %@", counter())
}

function main(a, b){
    testClosures()
    
    var zero = 0
    return zero.intValue
}
