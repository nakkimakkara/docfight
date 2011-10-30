import QtQuick 1.0

import com.nokia.meego 1.0

Item {
    id: dokumenttiNakyma

    signal backClicked()

    function save() {
        loggeri.doc = dokumentti.text
    }

    onVisibleChanged: if (visible) { dokumentti.text = loggeri.doc }

    function update() {
        // TODO: add header update
        dokumentti.text = loggeri.doc
    }

    Flickable {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.margins: 10
        contentHeight: dokumentti.height

        TextEdit {
            id: dokumentti
            text: ""

           onTextChanged: console.log("korkeus: "+ height)
        }
    }

    Header {
        id: header
    }
}
