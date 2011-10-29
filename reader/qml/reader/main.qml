import QtQuick 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    XmlListModel {
        id: modeli
        xml: loggeri.doclist

        query: "/feed/entry"
        namespaceDeclarations: "declare default element namespace 'http://www.w3.org/2005/Atom';"
        XmlRole {
            name: "title"
            query: "title/string()"
        }
    }

    Component {
        id: delegaatti
        Rectangle {
            height: text.height
            width: parent.width

            Text {
                id: text
                text: title
            }
        }
    }

    ListView
    {
        anchors.fill: parent
        model: modeli
        delegate: delegaatti
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
