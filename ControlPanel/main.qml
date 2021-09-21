import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.12
Window {
    id: window
    width: 1366
    height: 768
    visible: true
    title: qsTr("CONTROL PANEL")

    color: "transparent"


    Row {
        id: idRowBtn
        spacing: 20
        RoundButton {
            id: idBtnRunState
            width:  200
            height: 200
            radius: 10
            text: CUIModel.isRunning ?  "STOP" : "START"
            font.pixelSize: 50
            font.bold: true
            onClicked: {
                CUIModel.isRunning = !CUIModel.isRunning
            }
        }

        RoundButton {
            id: idBtnShowKeypad
            width:  100
            height: 100
            radius: 5
            text: "Toggle Keypad"
            onClicked: {
                console.log("onClicked")
                inputPanel.state = inputPanel.state == "" ? "visible" : ""
            }
        }
    }

    Item {
        id: idSliderBar

        width:  50
        height: 500

        anchors.left: idRowBtn.right
        anchors.leftMargin: 50

        Text {
            id: idSliderVal
            anchors.horizontalCenter: parent.horizontalCenter

            text: idSlider.value
            color: CUIModel.isRunning ? "green" : "orange"
            font.bold: true
            font.pixelSize: 25
        }

        Slider {
            id: idSlider
            anchors.top: idSliderVal.bottom
            anchors.bottom: idTextSpeed.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: 50
            orientation: Qt.Vertical
            stepSize: 1
            from: 0
            to:100
            enabled: CUIModel.isRunning

            onValueChanged:  {
                CUIModel.speed = value
            }
        }

        Text {
            id: idTextSpeed
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            text: CUIModel.isRunning ? "SPEED (running)" : "SPEED(idle)"
            color: CUIModel.isRunning ? "green" : "orange"
            font.bold: true
            font.pixelSize: 30
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
