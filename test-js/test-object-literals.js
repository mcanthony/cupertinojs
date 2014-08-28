/*
<expect>
platform.updatedAt Monday
platform["updatedAt"] Monday
platform.createdAt Sunday
platform["createdAt"] Sunday
NAMED NAMED
name turtle neck
NAMED KEYED
name turtle neck
NAMED NUMBERKEYED
platform.userInfo[2] 2
platform.userInfo[4] 4
NAMED NUMBERKEYED
platform.userInfo["2"] 2
platform.userInfo["4"] 4
platform.userInfo.status bim
platform["userInfo"].status boom
P["console"] console
</expect>
*/

function Platform(){
    this.userInfo = {
        "identifier" : "CUJS",
        "userInfo" : {
            "APIKey" : 42
        },
        2 : 2,
        "4" : 4,
    };

    this.name = "turtle neck"
}

function testTopLevelAccessors(){
    var platform = new Platform()
    platform["updatedAt"] = "Monday"
    platform.createdAt = "Sunday"

    cujs_log("platform.updatedAt %@", platform.updatedAt)
    cujs_log("platform[\"updatedAt\"] %@", platform["updatedAt"])
    cujs_log("platform.createdAt %@", platform.createdAt)
    cujs_log("platform[\"createdAt\"] %@", platform["createdAt"])

    cujs_log("NAMED NAMED")
    cujs_log("name %@", platform.name)

    cujs_log("NAMED KEYED")
    cujs_log("name %@", platform["name"])
}

function testNestedAccessors(){
    var platform = new Platform()

    cujs_log("platform[\"userInfo\"].identifier %@", platform["userInfo"].identifier)
    
    cujs_log("KEYED NAMED")
    cujs_log("platform.userInfo %@", platform.userInfo)
   
    platform.userInfo.identifier
    cujs_log("platform.userInfo.identifier %@", platform.userInfo.identifier)
    cujs_log("platform.userInfo[\"userInfo\"].APIKey %@", platform.userInfo["userInfo"].APIKey)

    var userInfo = platform.userInfo
    cujs_log("userInfo.identifier %@", userInfo.identifier)
    cujs_log("userInfo[\"identifier\"] %@", userInfo["identifier"])
}

function testKeyedVariant2(){
    var platform = new Platform()
    cujs_log("KEYED KEYED")
    cujs_log("platform.userInfo[\"identifier\"] %@", platform.userInfo["identifier"])
    cujs_log("platform.userInfo[\"userInfo\"][\"APIKey\"] %@", platform.userInfo["userInfo"]["APIKey"])
}

function testNumberSubScripting(){
    var platform = new Platform()
    cujs_log("NAMED NUMBERKEYED")
    cujs_log("platform.userInfo[2] %@", platform.userInfo[2])
    cujs_log("platform.userInfo[4] %@", platform.userInfo[4])
    
    cujs_log("NAMED NUMBERKEYED")
    cujs_log("platform.userInfo[\"2\"] %@", platform.userInfo["2"])
    cujs_log("platform.userInfo[\"4\"] %@", platform.userInfo["4"])   
}

function testNestedAssignment(){
    var platform = new Platform()
    platform.userInfo.status = "bim"
    cujs_log("platform.userInfo.status %@", platform.userInfo.status)
    
    platform["userInfo"].status = "boom"
    cujs_log("platform[\"userInfo\"].status %@", platform["userInfo"].status)
}

function testNumberStringSubscriptingEquality(){
    var platform = new Platform()

    var four = "4"
    cujs_log("platform.userInfo[four] (\"4\")%@", platform.userInfo[four])
    
    var four = 4
    cujs_log("platform.userInfo[four] (4)%@", platform.userInfo[four])
}

function testClassPropertyAssignmentSubscripting(){
    Platform.console = "console"
    cujs_log("P[\"console\"] %@", Platform["console"])
}

// FIXME: UNIMPLEMENTED
//    Platform[0] = "__first"
//    cujs_log("P[0] %@", Platform[0])

function main(a, b){
    testTopLevelAccessors()

//FIXME: once worked
//    testNestedAccessors()
    
//    testKeyedVariant2()
    
    testNumberSubScripting()
 
    testNestedAssignment()

    testClassPropertyAssignmentSubscripting()

    var zero = 0
    return zero.intValue
}
