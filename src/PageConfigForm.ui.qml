import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.settings 1.0
import io.qt.examples.langswitch 1.0

Page {
    id: page
    width: 400
    height: 600

    //property alias phone1PasswordCharacter: passTxt.passwordCharacter
    title: qsTr("Настройки приложения")

    Settings {
        property alias phone_num: phoneTxt.text
        property alias phone_pass: passTxt.text
        property alias sel_language: langTxt.text
    }

    Component.onDestruction: settings.state = page.state

    LangSwitch {
        id: langswitch
    }

    Button {
        y: 300
        text: "English"
        onClicked: langTxt.text=langswitch.userName= "en_US"

    }
    Button {
        y: 340
        text: "Russian"
        onClicked: text = langTxt.text=langswitch.userName= "ru_RU"
    }

    Label {
        text: qsTr("Настройки")
        anchors.centerIn: parent
    }

    TextField {
        id: phoneTxt
        x: 60
        y: 34
        width: 137
        height: 34
        //inputMask: qsTr("9999999999")
        text: ''
        //        text: qsTr("12345678")
        inputMethodHints: Qt.ImhDigitsOnly
        placeholderText: qsTr("Номер тел.")
        font.pixelSize: 18
    }

    TextField {
        id: langTxt
        x: 60
        y: 234
        width: 137
        height: 34
        //inputMask: qsTr("9999999999")
        text: 'ru_RU'
        //        text: qsTr("12345678")
        //placeholderText: qsTr("Номер тел.")
        font.pixelSize: 18
    }

    Label {
        id: label
        x: 32
        y: 39
        color: "#3f4549"
        text: qsTr("+7")
        anchors.bottom: phoneTxt.top
        anchors.bottomMargin: -28
        anchors.right: phoneTxt.left
        anchors.rightMargin: 0
        font.pointSize: 14
    }

    Label {
        id: label1
        x: 60
        y: 13
        text: qsTr("Номер телефона")
    }

    Label {
        id: label2
        x: 68
        y: 109
        text: qsTr("Пароль")
    }

    TextInput {
        id: passTxt
        x: 60
        y: 130
        width: 137
        height: 28
        text: qsTr("90512345678")
        inputMethodHints: Qt.ImhDigitsOnly
        font.pixelSize: 18
    }

    CheckBox {
        id: checkBoxPass
        x: 193
        y: 118
        text: qsTr("Показать пароль")
        checked: true
    }
}
