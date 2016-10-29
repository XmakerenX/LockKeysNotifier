import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: mainWindow
    x: Screen.width / 2 - 162
    y: Screen.height - 180
    visible: true
    width: 325
    height: 60
    color: "#00000000"
    property alias numlockOff: numlockOff
    property alias capsOn: capsOn
    opacity: 1
    title: qsTr("Keylcok Indicator")

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool
    objectName: "mainWindow"

    Image {
        id: capsOn
        x: 0
        y: 0
        width: 65
        height: 60
        visible: false
        source: "capslk_on.png"
        objectName: "capsOn"
    }

    Image {
        id: capsOff
        x: 0
        y: 0
        width: 65
        height: 60
        enabled: false
        clip: false
        visible: false
        source: "capslk_off.png"
        objectName: "capsOff"
    }

    Image {
        id: numlockOff
        x: 260
        y: 0
        width: 65
        height: 60
        enabled: false
        visible: false
        source: "numlk_off.png"
        objectName: "numlockOff"
    }

    Image {
        id: numlockOn
        x: 260
        y: 0
        width: 65
        height: 60
        visible: false
        source: "numlk_on.png"
        objectName: "numlockOn"
    }
}
