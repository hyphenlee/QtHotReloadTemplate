import QtQuick
import QtQuick.Window
import QtQuick.Controls
Window {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property string last_source: ""
    property bool flag: false
    Loader{
        x:100
        y:100
        id:load1
        source:last_source
    }

    Button{
        text:"switch"
        onClicked: {
            if(flag){
                last_source="Component1/Module2.qml"
            }else{
                 last_source="Component1/Module1.qml"
            }
            flag=!flag
        }
    }
    Component.onCompleted: {
        last_source="Component1/Module1.qml"

    }
    function reload(){
        console.log("reload qml")
        var source=last_source
        last_source=""
        last_source=source
    }
}
