import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import Qt.labs.platform 1.0


import "basic"
import "setting"

Window {
    visible: true
    width: 640
    height: 480
    //flags: Qt.FramelessWindowHint

    Component.onCompleted: {
        for(var i=0; i< 50; i++) {
            listModel.append({name:"a"+i})
        }
    }


    Flow {
        id: sshctl
        anchors.fill: parent
        spacing: 3
        Repeater{
             model: ListModel{
                 id: listModel
             }
             Button {
                 text: model.name
             }
        }
    }
}
