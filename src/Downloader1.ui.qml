import QtQuick 2.12
import QtQuick.Controls 2.5

import com.blackgrain.qml.quickdownload 1.0
import io.qt.examples.langswitch 1.0

import Qt.labs.platform 1.1
import QtQuick.Dialogs 1.2

import "common/check_update.js" as CheckUpdate

Item {

    property int request_VIEW_FILE_PDF: 21
    property string globalHash: '';
    id: appWindow
    LangSwitch {
        id: langswitch
    }

    TextEdit {
        id: logEdit
        x: 20
        y: parent.width - 100
        color: "yellow"
        width: parent.width - 40
        height: 167
        wrapMode: TextEdit.WrapAnywhere
        text: qsTr("Text Edit")
        font.pixelSize: 12
    }

    TextArea {
        id: textAreaVer
        x: 20
        y: 80
        color: "#a40000"
        text: qsTr(Qt.application.version)
        //anchors.top: parent.top
        anchors.topMargin: 80
        font.pixelSize: 12
    }

    TextArea {
        id: textArea2
        x: 20
        y: 120
        color: "white"
        width: 600
        height: 200
        text: ""
    }

    TextArea {
        id: textArea
        x: 20
        y: 350
        width: 600
        height: 200
        visible: false
        text: ""
    }

    TextInput {
        id: texturl
        //x: 114
        y: parent.height-140
        x: 20
        color: "yellow"

        width: parent.width - 120
        height: 20
        text: qsTr("/data/user/0/org.qtproject.qtview/files/share_example_x_files")
        font.pixelSize: 18
    }

    Text {
        id: downurl
        font.pixelSize: 12
        textFormat: Text.RichText
        font.italic: true
        text: Qt.locale().name.substring(0,2)
        // "ioi(<a href=\"" + link + "\">Link</a>)" ? text : "..."
        // anchors.centerIn: parent
        x: 20
        y: 180
        onLinkActivated: {
            Qt.openUrlExternally(link)
        }
    }



    Button {
        x: parent.width - checkupdatebtn.width - 20
        id: checkupdatebtn
        y: 80

        text: "Check Update"
        onClicked: {

            console.log('before start checkupdate')
            CheckUpdate.myCheckupdate()
            console.log('after start checkupdate')
            // texturl.text = langswitch.getnewAppPath
            logEdit.text = download2.hashsum + '\n' + logEdit.text
        }
    }

    Button {
        x: checkupdatebtn.x - downloadButton.width - 20
        y: 80
        id: downloadButton
        enabled: false
        text: "D start"
        onClicked: {
            //download1.running = true
            // download1.start
            langswitch.setAppPath = texturl.text;
            console.log('cppp setAppPath done');
            console.log('before cpp value is' + langswitch.getnewAppPath);
            texturl.text = langswitch.getnewAppPath + "/dev-preview.apk";
            langswitch.setAppPath = texturl.text;
            download2.destination = texturl.text;
            console.log('QML url download is =' + download2.destination);
            download2.running = true;
            download2.start;
            //download3.running = true
            // download3.start
        }
    }

    Button {
        x: 200
        y: 0
        text: "Open"
        onClicked: {
            fileDialog.folder = texturl.text
            fileDialog.visible = true
            fileDialog.Open
            // texturl.text= fileDialog.fileUrls
            //fileDialog.Open
        }
    }

    Button {
        x: 280
        y: 0
        text: " Get. "
        //onClicked: folderDialog.open()
        onClicked: {
            console.log('getnewapppath')
            console.log('result cpp is ' + langswitch.getnewAppPath)
            texturl.text = langswitch.getnewAppPath
        }
    }

//    Button {
//        y: 40
//        text: "@apk"
//        onClicked: {
//            //logEdit.text= folderDialog.folder + '\n' + logEdit.text
//            //folder: texturl.text
//            //Qt.openUrlExternally(texturl.text);
//            //shareUtils.share("Qt","http://qt.io");
//            //shareUtils.share("Qt", texturl.text)


//            if (Qt.platform.os === "android")
//            {
//            shareUtils.viewFile(texturl.text, "View File",
//                                "application/vnd.android.package-archive",
//                                request_VIEW_FILE_PDF, appWindow.useAltImpl)
//}
//            else
//            {
//                console.log('not android platform');
//             logEdit.text = 'Not android platform\n' + logEdit.text;
//            }
//            console.log('return from cpp ');
//            //download2.InstallApp=texturl.text.toString();
//            //langswitch.setAppPath = texturl.text;
//            //           console.log('return from cpp ' + langswitch.setAppPath(texturl.text));
//            logEdit.text = 'done\n' + logEdit.text
//        }
//    }

    FolderDialog {
        id: folderDialog
        currentFolder: ""
        // StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onFolderChanged: {
            texturl.text = folder
            //logEdit.text= folder + '\n' + logEdit.text
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: {
        // /storage/emulated/0/download
            if (texturl.text != '/data/user/0/org.qtproject.qtview/files/share_example_x_files') {
                console.log('custom path =' + texturl.text)
                fileDialog.folder = shortcuts.home
                texturl.text = shortcuts.home
            } else {
                console.log('custom path =' + texturl.text)
                fileDialog.folder = texturl.text
            }
        }
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            texturl.text = fileDialog.fileUrls[0]
            logEdit.text = fileDialog.fileUrls[0] + '\n' + logEdit.text
            //Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            //Qt.quit()
        }
        Component.onCompleted: visible = false
    }

//    Button {
//        x: 100
//        y: 40
//        text: "Set path"
//        onClicked: {
//            console.info('start setAppPath')
//            langswitch.setAppPath = texturl.text
//            // console.log('setAppPath done and returned is =' + fff)
//            //m_appPath = fff
//            console.info('done setAppPath')
//        }
//    }

    Button {
        y: 0
        text: "Stor Req"
        onClicked: {
            console.info('permsreq requested before')
            if (langswitch.requestPermissions) {
                // allowed local storage permissions
                console.info('permsreq Allowed storage ok')
            } else {
                // no permissions to local storage
                console.info('permsreq Deny storage false')
            }

            console.info('permsreq function done')
            //console.log(langswitch.requestPermissions())
            //langswitch.setAppPath(texturl.text);
        }
    }

    Download {
        id: download1

        url: "http://placehold.it/350x150"
        //destination: "file:///tmp/test.png"
        overwrite: true
        destination: {

            //       "file://" + langswitch.getnewAppPath + "/test.png"
            console.log(download1.destination)
        }

        //        running: true
        running: false

        followRedirects: true
        onRedirected: console.log('Redirected', url, '->', redirectUrl)

        onStarted: {
            console.log('Started download', url)
        }
        onError: console.error(errorString)
        onProgressChanged: console.log(url, 'progress:', progress)
        onFinished: console.info(url, 'done')
    }

    Download {
        id: download2
        hashsum: '0b3af23ea69818b8666cc218b0285964b400172ad6db755cd7b6952baa80de5ecc26df971724131736675c13444262742070a45012c1008a2b434e2a7bcfece6'
        //url: "ftp://speedtest.tele2.net/5MB.zip"
        url: "https://github.com/fly" + "true"
             + "/dev-apk1/releases/download/0.0.5/" + "dev-preview.apk"
        //destination: "file:///tmp/QuickDownload_test.zip"
        destination: {
            console.log('change distanation QML')
            "file://" + langswitch.getnewAppPath + "/QuickDownload_test.zip"
            console.log(download2.destination)
            console.log('changed distanation QML')
            //         runningChanged.: {
            //                logEdit.text= download2.progress + '\n' + logEdit.text;
            //            }
        }

        overwrite: true
        //        running: !download1.running
        running: false
        followRedirects: true
        onStarted: console.log('Started download', url)
        onError: console.error(errorString)
        onProgressChanged: {
            console.log(url, 'progress:', progress)
            progressBar.value = progress
            //logEdit.text= progress + ' progress\n' + logEdit.text;
        }
        onFinished: {
            console.log(url,
                        'qml download is done-qml onFineshed function hash ='
                        + download2.hashsum.toString(
                            ) + ' for file=' + langswitch.getnewAppPath)
            // 6 = QCryptographicHash::Sha512
            //console.log('checksum returned is ' + check_sum_file_sha512(download2.destination));
            console.log('checksum returned is ' + check_sum_file_sha512(
                            langswitch.getnewAppPath))
            console.log('read result with hashsumresult is = ' + hashsumresult)
            console.log('original summ is ' + download2.hashsum)
            if (hashsumresult == CheckUpdate.hash_set()) {
                console.log('checksum is ok')
                logEdit.text = 'file checksum is [OK] :)))) \nAnd launch '
                        + langswitch.getnewAppPath + '\n' + logEdit.text
                logEdit.text = 'And launch 2 ' + remove_qrc(
                            langswitch.getnewAppPath) + '\n' + logEdit.text
                //Qt.openUrlExternally(remove_qrc(langswitch.getnewAppPath));

                if (Qt.platform.os === "android")
                {
                shareUtils.viewFile(texturl.text, "View File",
                                    "application/vnd.android.package-archive",
                                    request_VIEW_FILE_PDF, appWindow.useAltImpl)
    }
                else
                {
                    console.log('not android platform');
                 logEdit.text = 'Not android platform\n' + logEdit.text;
                }


            } else {
                console.log('checksum not ok')
                logEdit.text = 'ERROR file checksum is not OK :(((( \n\n' + logEdit.text
            }
        }
    }

    ProgressBar {
        id: progressBar
        x: 111
        y: 367
        width: parent.width
        height: 16
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        value: 0.0
    }

    Download {
        id: download3

        url: "ftp://demo:password@test.rebex.net/readme.txt"
        //destination: "file:///tmp/QuickDownload_test_readme.txt"
        destination: "file://" + langswitch.getnewAppPath + "/QuickDownload_test_readme.txt"

        overwrite: true
        running: false

        onStarted: console.log('Started download', url)
        onError: console.error(errorString)
        onProgressChanged: console.log(url, 'progress:', progress)
        onFinished: console.info(url, 'done')
    }
}
