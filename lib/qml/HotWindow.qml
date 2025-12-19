import QtQuick
import QtQuick.Window
Window {
    property string last_source: ""
    property string old_source: ""
    property int count:0 
    Loader{
        x:100
        y:200
        id:load1
        source:last_source
    }
    function clear(){
        console.log("clear source")
        old_source=last_source
        last_source=""
    }
    function reload(){

        
        if(count++ % 2 ==1){
                    console.log("reload qml")
            last_source=old_source
        }
    }
    Component.onDestruction: {
        console.log("destruct main qml")
    }
    
}
