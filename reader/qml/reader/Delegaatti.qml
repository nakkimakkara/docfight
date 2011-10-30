import QtQuick 1.0
import "UiConstants.js" as UI

Component {
    id: delegaatti
    Rectangle {
        height: contentColumn.height + contentColumn.anchors.margins * 2
        width: parent.width
        anchors.margins: 10

        Gradient {
            id: blurGradient
            GradientStop {position: 0; color: "#ffffff"}
            GradientStop {position: 0.01; color: "#bbbbbb"}
            GradientStop {position: 0.99; color: "#bbbbbb"}
            GradientStop {position: 1; color: "#999999"}
        }
        Gradient {
            id: focusGradient
            GradientStop {position: 0; color: "#dddddd"}
            GradientStop {position: 0.01; color: "#bbbbbb"}
            GradientStop {position: 0.99; color: "#bbbbbb"}
            GradientStop {position: 1; color: "#777777"}
        }
        gradient: mouseArea.containsMouse ? focusGradient : blurGradient

        Column {
            id: contentColumn
            spacing: 5
            anchors.margins: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                id: text
                text: title
                font.pixelSize: UI.ListFontSize
                //                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            Row {
                opacity: 0.7
                spacing: 5
                anchors.left: parent.left
                Text {
                    font.pixelSize: UI.ListLastViewFontSize
                    color: "#5555ff"

                    text: "Last viewed on:"
                }

                Text {
                    id: lastViewedText
                    text: lastViewed
                    font.pixelSize: UI.ListLastViewFontSize
                    color: "#5555ff"

                    //                anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent

            onClicked: {
                console.log("Requesting document for id: " + resourceId);
                loggeri.requestDocument(resourceId)
            }
        }
    }
}
