import QtQuick 1.0

import com.nokia.meego 1.0

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

    ToolBar {
        anchors.bottom: parent.bottom
    }

    Flickable {
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        contentHeight: dokumentti.height

        TextEdit {
            id: dokumentti
            text: ""

           onTextChanged: console.log("korkeus: "+ height)
        }
    }
}
