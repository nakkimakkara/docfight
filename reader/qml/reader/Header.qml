import QtQuick 1.0

Rectangle {
    property alias text: headerText.text

    id: header
    height: headerText.height + 50
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    color: "#2222ff"

    Text {
        id: headerText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 15
        font.pixelSize: 26
        font.family: "Nokia pure"
        text: "Google Docs"
        color: "white"
    }
}
