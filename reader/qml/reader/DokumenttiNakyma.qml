import QtQuick 1.0

Item {
    id: dokumenttiNakyma

    signal backClicked()

    onVisibleChanged: if (visible) { dokumentti.text = loggeri.doc }

    Rectangle {
        id: topBar
        height: 40
        width: parent.width
        anchors {top: parent.top}

        Rectangle {
            color: "red"
            width: 50
            height: parent.height

            MouseArea {
                anchors.fill: parent

                onClicked: backClicked()
            }
        }
    }

    Text {
        id: dokumentti
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        text: ""
    }
}
