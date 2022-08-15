import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Rectangle{
        width: 100
        height: 100
        color: 'red'
        Button{
            text: '24fd3'
            onClicked: {

            }

        }
    }
Component.onDestruction: {
    console.log("destruct module1")
}
}
