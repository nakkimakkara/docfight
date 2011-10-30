import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    initialPage: mainPage

    color: "#eeeeee"

    MainPage {
        id: mainPage
    }

    ToolBarLayout {
        id: commonTools
        visible: true
//        ToolIcon {
//            platformIconId: "toolbar-save"
//            anchors.right: (parent === undefined) ? undefined : parent.right
//            onClicked: (myMenu.status == DialogStatus.Closed) ? myMenu.open() : myMenu.close()
//        }
        ToolIcon {
            platformIconId: "toolbar-save"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: mainPage.save()
        }
        ToolIcon {
            platformIconId: "toolbar-back"
            anchors.left: (parent === undefined) ? undefined : parent.left
            onClicked: mainPage.back()
        }
    }

    Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: qsTr("Nothing to see here") }
        }
    }
}
