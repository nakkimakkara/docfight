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
        dokumentti.text = loggeri.doc
    }

    Flickable {
        anchors.fill: parent
        anchors.margins: 10
        contentHeight: dokumentti.height

        TextEdit {
            id: dokumentti
            text: ""

           onTextChanged: console.log("korkeus: "+ height)
        }
    }
}
