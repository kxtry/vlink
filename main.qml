import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import KxFileContent 1.0
import KxRegexp 1.0


import "basic"
import "setting"

Window {
    visible: true
    width: 640
    height: 480
    //flags: Qt.FramelessWindowHint

    Component.onCompleted: {
        var content = config.content
        var sshs = regex.capturedTexts(content)
        console.log(sshs)
        for(var i = 0; i < sshs.length; i++) {
            var items = sshs[i].split(' ')
            for(var j = 0; j < items.length; j++) {
                listModel.append({name:items[j]})
            }
        }
    }

    KxRegexp {
        id: regex
        pattern: "Host\\s([^\\r|\\n]*)"
    }

    KxFileContent {
        id: config
        filename: "H:/tools/kxtry/myssh/config"
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
