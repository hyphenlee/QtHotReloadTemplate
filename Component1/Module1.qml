import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Rectangle{
        width: 100
        height: 100
        color: 'yellow'
        Button{
            text: '34343'
            onClicked: {

            }

        }
    }
Component.onDestruction: {
    console.log("destruct module1")
}
}
