import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Text{
        text:'module one'
    }
    Rectangle{
        id:'rect'
        width: 200
        height: 200
        color: 'green'
        Button{
            text: "hello" 
            onClicked: { 
                rect.color='yellow'
            }
        }
    } 
    
Component.onDestruction: {
    console.log("destruct module1")
}
Component.onCompleted:{
        console.log("create module1")
    }
}
