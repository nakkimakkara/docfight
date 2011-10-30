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
            GradientStop {position: 0.02; color: "#dddddd"}
            GradientStop {position: 0.98; color: "#dddddd"}
            GradientStop {position: 1; color: "#999999"}
        }
        Gradient {
            id: focusGradient
            GradientStop {position: 0; color: "#dddddd"}
            GradientStop {position: 0.02; color: "#bbbbbb"}
            GradientStop {position: 0.98; color: "#bbbbbb"}
            GradientStop {position: 1; color: "#777777"}
        }
        gradient: mouseArea.containsMouse ? focusGradient : blurGradient

        Image {
            function iconForResource(resourceId) {
                if (resourceId.indexOf("document:") !== -1) {
                    return "https://ssl.gstatic.com/docs/doclist/images/icon_9_document_list.png"
                } else {
                    return "https://ssl.gstatic.com/docs/doclist/images/icon_9_spreadsheet_list.png"

                }
            }

            id: icon
            source: iconForResource(resourceId)
            anchors.margins: 10
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
        }

        Column {
            id: contentColumn
            spacing: 5
            anchors.margins: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.right
            anchors.right: parent.right

            Text {
                id: text
                text: title
                font.pixelSize: UI.ListFontSize
                anchors.left: parent.left
            }
            Row {
                spacing: 5
                anchors.left: parent.left
                Text {
                    font.pixelSize: UI.ListLastViewFontSize
                    color: "#2222ff"

                    text: "Last viewed on:"
                }

                Text {
                    id: lastViewedText
                    text: lastViewed
                    font.pixelSize: UI.ListLastViewFontSize
                    color: "#2222ff"
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
