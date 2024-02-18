import QtQuick
import QtQuick.Window
Window {
    property string last_source: ""
    Loader{
        x:100
        y:200
        id:load1
        source:last_source
    }
    function reload(){
        console.log("reload qml")
        var source=last_source
        last_source=""
        last_source=source
    }
    Component.onDestruction: {
        console.log("destruct main qml")
    }
    
}
