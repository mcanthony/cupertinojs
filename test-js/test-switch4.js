/*
<expect>
switchLog: 2
switch 2: 0
switch 2: 1
switch 2: 2
after for
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
        case 1337: {
            cujs_log("switch 1: %@", j)
            break
        }
        case 2: {
            for (var i = 0; i < 10; i++){
                cujs_log("switch 2: %@", i)
                if (i == j)
                    break
            }
            
            cujs_log("after for", j)
        }
        default:{
            cujs_log("default")
            break
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