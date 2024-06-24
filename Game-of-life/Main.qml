import QtQuick
import QtQuick.Controls
import Game_of_life

Window {
    // width: 640
    // height: 480
    width: Screen.width - 20
    height: Screen.height - 80
    visible: true
    color: "black"
    title: qsTr("Game of Life")

    Item {
        id: rootItem

        anchors.fill: parent

        TableView {
            id: grid

            property int uselessProperty: {
                console.log(Object.keys(Driver.model))
                console.log("rows : " + Driver.model.rowCount())
                console.log("cols : " + Driver.model.columnCount())
                return 0
            }

            anchors.centerIn: parent
            width: parent.width - 20
            height: parent.height - 20

            model: Driver.model

            delegate: Item {
                id: entity

                required property bool isAlive
                property int sideLength: 5

                implicitWidth: sideLength
                implicitHeight: sideLength

                Rectangle {
                    anchors.fill: parent
                    color: parent.isAlive? "yellow" : "grey"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        entity.isAlive ^= 1
                    }
                }
            }
        }
    }
}
