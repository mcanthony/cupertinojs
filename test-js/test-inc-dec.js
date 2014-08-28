/*
<expect>
value: 1
value after: 2
value: 2
value after: 2
value: 1
value after: 0
value: 0
value after: 0
</expect>
*/

function testIncPostFix(){
    var i = 1
    cujs_log("value: %@", i++);
    cujs_log("value after: %@", i);
}

function testIncPreFix(){
    var i = 1
    cujs_log("value: %@", ++i);
    cujs_log("value after: %@", i);
}

function testDecPostFix(){
    var i = 1
    cujs_log("value: %@", i--);
    cujs_log("value after: %@", i);
}

function testDecPreFix(){
    var i = 1
    cujs_log("value: %@", --i);
    cujs_log("value after: %@", i);
}

function main(a, b){
    testIncPostFix()
    testIncPreFix()
    testDecPostFix()
    testDecPreFix()
    
    var zero = 0
    return zero.intValue
}
