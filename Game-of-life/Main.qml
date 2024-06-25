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

        property bool started: false

        function togglePlayback() {
            started ^= 1
            Driver.togglePlayback()
        }


        Keys.onPressed: (event) => {
            if (event.key === Qt.Key_Space) {
                console.log("space pressed")
                togglePlayback()
            }
        }

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

            property int sideLength: Driver.sideLength

            columnWidthProvider: function(column) {
                return sideLength
            }

            rowHeightProvider: function(row) {
                return sideLength
            }

            delegate: Rectangle {
                id: entityBox

                implicitWidth: 10
                implicitHeight: 10

                border.width: 1
                color: model.isAlive? "yellow" : "grey"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        model.isAlive ^= 1
                    }
                }
            }

            Connections {
                target: Driver

                function onSideLengthChanged(newLen) {
                    console.log("side length changed")

                    grid.sideLength = newLen
                    grid.forceLayout()
                }
            }
        }

        component BlueButton :Rectangle {

            property alias text: label.text

            signal buttonClicked

            width: 150
            height: 50
            radius: width / 3
            border.width: 3
            border.color: "black"

            color: "darkblue"

            Label {
                id: label
                anchors.centerIn: parent
                font.pixelSize: 20
                color: "white"
            }

            MouseArea {

                anchors.fill: parent
                onPressed: {
                    parent.color = "blue"
                    parent.border.color = "darkblue"
                    label.color = "lightgrey"
                }
                onReleased: {
                    parent.color = "darkblue"
                    parent.border.color = "black"
                    label.color = "white"
                }

                onClicked: {
                    buttonClicked()
                }
            }
        }

        BlueButton {
            id: startAndStopButton

            text: rootItem.started? "Stop" : "Start"

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 20

            onButtonClicked: {
                console.log("mouse: toggle start")
                rootItem.togglePlayback()
            }
        }

        BlueButton {
            id: nextButton

            text: "Next"

            anchors.bottom: parent.bottom
            anchors.left: startAndStopButton.right
            anchors.bottomMargin: 20
            anchors.leftMargin: 20

            onButtonClicked: {
                console.log("next is pressed")
                Driver.goToNextGen();
            }
        }

        Slider {
            id: sizeSlider

            from: 10
            to: 50
            stepSize: 5
            value: Driver.sideLength

            anchors.verticalCenter: nextButton.verticalCenter
            anchors.left: nextButton.right
            anchors.leftMargin: 20

            onValueChanged: {
                Driver.setSideLength(sizeSlider.value)
            }
        }

        Component.onCompleted: {
            forceActiveFocus()
            Driver.setSideLength(sizeSlider.value)
        }
    }
}
