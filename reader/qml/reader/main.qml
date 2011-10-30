import QtQuick 1.0
import "UiConstants.js" as UI

Rectangle {
    width: 360
    height: 360

    //    anchors.fill: parent

    states: [
        State {
            name: UI.MainListState
            PropertyChanges {
                target: dokumenttiListaNakyma
                visible: true
            }
        },
        State {
            name: UI.MainDocState
            PropertyChanges {
                target: dokumenttiNakyma
                visible: true
            }
        }
    ]

    state: "listaNakyma"

    DokumenttiListaNakyma {
        id: dokumenttiListaNakyma
        anchors.fill: parent
        visible: false
    }

    DokumenttiNakyma {
        id: dokumenttiNakyma
        anchors.fill: parent
        visible: false

        onBackClicked: state = UI.MainListState
    }

    Connections {

    }
}
