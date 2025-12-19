import QtQuick
import QtQuick.Window
import QtQuick.Controls
import "lib/qml"
HotWindow{
    id:root
    width: 640
    height: 480
    visible:true
    /* title: qsTr("Hello World") */
    title: Env.GetRootPath()
    property bool flag: false
    property string rootPath:Env.GetRootPath()
    /* Loader{ */
    /*     x:100 */
    /*     y:200 */
    /*     id:load1 */
    /*     source:last_source */
    /* } */

    Button{
        text:"switch"
        onClicked: {
            if(flag){
                /* last_source=rootPath+"/Component1/Module2.qml" */
                last_source=""
            }else{
                 last_source=rootPath+"/Component1/Module1.qml"
            }
            flag=!flag
        }
    }
    Component.onCompleted: {
        last_source=rootPath+"/Component1/Module1.qml"

        
    }

    Component.onDestruction: {
        console.log("destruct main qml")
    }
}

