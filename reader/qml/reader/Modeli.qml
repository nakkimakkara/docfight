import QtQuick 1.0

XmlListModel {
    id: modeli
    xml: loggeri.docList

    query: "/feed/entry"
    namespaceDeclarations: "declare default element namespace 'http://www.w3.org/2005/Atom'; declare namespace gd = 'http://schemas.google.com/g/2005';"
//    namespaceDeclarations: "declare default element namespace 'http://www.w3.org/2005/Atom';"

    XmlRole {
        name: "title"
        query: "title/string()"
    }

    XmlRole {
        name: "resourceId"
        query: "gd:resourceId/string()"
    }

    XmlRole {
        name: "lastViewed"
        query: "gd:lastViewed/string()"
    }
}
