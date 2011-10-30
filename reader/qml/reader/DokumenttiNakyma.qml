import QtQuick 1.0

Item {
    id: dokumenttiNakyma

    signal backClicked()

    onVisibleChanged: if (visible) { dokumentti.text = loggeri.doc }

    function update() {
        dokumentti.text = loggeri.doc
    }

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

                onClicked: {
                    console.log("Back clicked")
                    dokumenttiNakyma.backClicked()
                }
            }
        }
    }

    Flickable {
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        contentHeight: dokumentti.height
        Text {
            id: dokumentti
            text: ""
        }
    }
}
