import QtQuick 1.0

import com.nokia.meego 1.0

Item {
    id: dokumenttiNakyma

    signal backClicked()

    onVisibleChanged: if (visible) { dokumentti.text = loggeri.doc }

    function update() {
        dokumentti.text = loggeri.doc
    }

    Flickable {
        anchors.top: parent.top
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
