// import QtQuick 2.12
// import QtQuick.Controls 2.5
// import QtQuick.Controls.Material 2.0
import QtQuick 2.12
import QtQuick.Controls 2.12



Page {
    width: 400
    height: 600

    title: qsTr("Page 2")



    Loader {
        id: pageLoader
        onStatusChanged: if (pageLoader.status == Loader.Ready) {
                             console.log('Loaded from url')
                            statusline.text = 'Download ok'
                         } else
                         {
                             statusline.text = 'error download from url'
                             console.log('error loading. local run')

                             //statuslinetimer.stop()
                             //statuslinetimer.start()
                             pageLoader.source = "Page1Form.ui.qml"
                         }
    }

    Label {
        text: qsTr("You are on Page 2.")
 //       anchors.centerIn: parent
        x : 200
    }

    Button {
        id: button321
        x: 51
        y: 28
        text: qsTr("Проверить баланс")
    }

    Connections {
        target: button321
        onClicked: {
            // balbalance.text = ' Баланс 123'
           // langswitch.userName = 'text'
            statusline.text = qsTr("loading")
            statuslinetimer.start()
            pageLoader.source = "https://raw.githubusercontent.com/homdx/qt-rssnews/master/src/example1.qml"
            backend

}
}
}
