import QtQuick 2.4

Item {
    width: 400
    height: 400

    TextInput {
        id: textInput
        x: 47
        y: 38
        width: 80
        height: 20
        text: qsTr("Text Input")
        font.pixelSize: 12
    }

    ListView {
        id: listView
        x: 122
        y: 192
        width: 110
        height: 160
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                spacing: 10
            }
        }
    }

    Text {
        id: text1
        x: 143
        y: 99
        text: qsTr("Hola")
        font.pixelSize: 12
    }
}
