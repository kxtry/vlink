import QtQuick 2.6
import QtQuick.Window 2.2

import "basic"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Component {
             id: redSquare

             Rectangle {
                 color: "red"
                 width: 100
                 height: 100
             }
         }

    Rectangle {
        color: "green"
        width: 100
        height: 100
    }

    Loader { sourceComponent: redSquare; y: 120 }
    Loader { sourceComponent: redSquare; x: 120 }

    KxTheme {
        id:g_theme
    }
}
