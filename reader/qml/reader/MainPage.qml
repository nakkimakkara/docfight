import QtQuick 1.0
import com.nokia.meego 1.0
import "UiConstants.js" as UI

Page {
    tools: commonTools

    function back() {
        root.state = UI.MainListState
    }

    function save() {
        dokumenttiNakyma.save()
    }

    Rectangle {
        id: root
        anchors.fill: parent

        states: [
            State {
                name: UI.MainListState
                PropertyChanges {
                    target: dokumenttiListaNakyma
                    visible: true
                }
                PropertyChanges {
                    target: dokumenttiNakyma
                    visible: false
                }
            },
            State {
                name: UI.MainDocState
                PropertyChanges {
                    target: dokumenttiListaNakyma
                    visible: false
                }
                PropertyChanges {
                    target: dokumenttiNakyma
                    visible: true
                }
            }
        ]

        state: UI.MainListState

        DokumenttiListaNakyma {
            id: dokumenttiListaNakyma
            anchors.fill: parent
            visible: false
        }

        DokumenttiNakyma {
            id: dokumenttiNakyma
            anchors.fill: parent
            visible: false

            onBackClicked: {
                console.log("signal received")
                root.state = UI.MainListState
            }
        }

        Connections {
            target: loggeri
            onDocChanged:
            {
                dokumenttiNakyma.update()
                root.state = UI.MainDocState
            }
        }
    }
}
