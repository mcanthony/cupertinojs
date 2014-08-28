/*
<expect>
(null)
</expect>
*/

objc_import("test-imports.h")

function testImportedInterface(){
    //There will be an interface
    //but no implementation here
    cujs_log("%@", ZooObject)
}

function main(a, b){
    testImportedInterface()
    
    var zero = 0
    return zero.intValue
}
