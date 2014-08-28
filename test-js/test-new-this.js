/*
<expect>
final count: 3
</expect>
*/

function Counter(init){
    this.value = init
    
    function increment(){
        this.value = this.value + 1
    }
    
    this.increment = increment
    return this
}

function testNewThis(){
    var c = new Counter(1)
    c.increment()
    c.increment()
    
    cujs_log("final count: %@", c.value)
}

function main(a, b){
    testNewThis()
   
    var zero = 0
    return zero.intValue
}

