import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: window
    visible: true
    width: 400
    height: 480
    title: qsTr("Stack")
    property alias balbalance : balbalance.text
    property alias statusline : statusline.text
    property alias statuslinetimer: timerid
    Material.theme: Material.Dark
    Material.accent: Material.Purple
    //themeSwitch.checked
                    //? Material.Dark : Material.Light


    Timer {
        id : timerid
        interval: 5000; running: false; repeat: false
        onTriggered: {
            console.log('timer end');
            statusline.text = '';

    }
}

    footer: Text {
        id: statusline
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight


        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Заказы")
                width: parent.width
                onClicked: {
                    stackView.push("PageHistoryForm.ui.qml")
                    drawer.close()
                }
}

            ItemDelegate {
                text: qsTr("Обновление")
                width: parent.width
                onClicked: {
                    stackView.push("Page1Form.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {

                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }


            ItemDelegate {
                text: qsTr("Настройки")
                id: config
                width: parent.width
                onClicked: {
                    stackView.push("PageConfigForm.ui.qml")
                    drawer.close()
                }

            }

            ItemDelegate {
                id: balbalance
                x: config.x + 10

                text: { balbalance.text = '\n\nБаланс ' }
                }

        }
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }
}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
