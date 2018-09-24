import QtQuick 2.6
import QtQuick.Window 2.2

import "basic"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    KxTheme {
        id:g_theme
    }
}
