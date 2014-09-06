/*
<expect>
switchLog: 2
switch 2: 2
default
after: 2
switchLog: 1337
switch 1: 1337
after: 1337
switchLog: 0
default
after: 0
done
</expect>
*/

function switchLog(j){
    cujs_log("switchLog: %@", j)
    switch (j) {
        default:{
            cujs_log("default")
        }
        case 1337: {
            cujs_log("switch 1: %@", j)
            break
        }
        case 2: {
            cujs_log("switch 2: %@", j)
        }
    }
    
    cujs_log("after: %@", j)
}

function testSwitch(){
    switchLog(2)
    switchLog(1337)
    switchLog(0)
}

function main(a, b){
    testSwitch()
    cujs_log("done")
    
    var zero = 0
    return zero.intValue
}