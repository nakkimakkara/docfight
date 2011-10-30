import QtQuick 1.0

Item {
    id: dokumenttiListaNakyma

    Modeli {
        id: modeli
    }

    Delegaatti {
        id: delegaatti
    }

    DokumenttiLista {
        id: dokumenttiLista
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Header {
        id: header
    }
}
