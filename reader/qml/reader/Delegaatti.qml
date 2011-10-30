import QtQuick 1.0
import "UiConstants.js" as UI

Component {
    id: delegaatti
    Rectangle {
        height: text.height + text.anchors.margins * 2
        width: parent.width

        Gradient {
            id: blurGradient
            GradientStop {position: 0; color: "#eeeeee"}
            GradientStop {position: 1; color: "#bbbbbb"}
        }
        Gradient {
            id: focusGradient
            GradientStop {position: 0; color: "#bbbbbb"}
            GradientStop {position: 1; color: "#777777"}
        }
        gradient: mouseArea.containsMouse ? focusGradient : blurGradient

        Text {
            id: text
            text: title
            font.pixelSize: UI.ListFontSize
            anchors.margins: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
        }
        Text {
            id: lastViewedText
            text: lastViewed
            font.pixelSize: UI.ListFontSize
            anchors.margins: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent

            onClicked: {
                console.log("Requesting document for id: " + resourceId);
                loggeri.requestDocument(resourceId)
            }
        }

        Component.onCompleted: {
            console.log(title)
        }
    }
}
