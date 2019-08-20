//import QtQuick 2.12
//import QtQuick.Controls 2.5

//Page {
//    id: page
//    width: 400
//    height: 600

//    title: qsTr(Qt.application.version) ? title : qsTr("Home")
import QtQuick 2.12
import QtQuick.Controls 2.5
//1.4
import QtQuick.Layouts 1.1

Page {
    visible: true
    width: 640
    height: 480
     title: qsTr(Qt.application.version) ? title : qsTr("Home")

    // Слой в котором располагается TextInput и Button
    RowLayout {
        id: rowLayout
      //  anchors.top: parent.top
      //  anchors.left: parent.left
      //  anchors.right: parent.right
        anchors.margins: 5
        height: 30

        spacing: 5
        z:2         /* Уровень расположения слоёв элементов.
                     * Элемент с z = 2 располагается выше, чем элемент с z = 1
                     */

        // Область с TextInput
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"

//            TextInput {
//                y: 20
//                x: 230
//                id: textInput
//                //anchors.fill: parent
//                //horizontalAlignment: Text.AlignHCenter
//                //verticalAlignment: Text.AlignVCenter

//                /* По нажатию клавиши Enter передаём информацию
//                 * из TextInput в элемент ListView
//                 * */
//                Keys.onPressed: {
//                    // 16777220 - код клавиши Enter
//                    if(event.key === 16777220){
//                        listModel.append({ textList: textInput.text })
//                    }
//                }
//            }
        }

        /* Кнопка, по нажатию которой передаётся информация из
         * textInput в элемент ListView
         * */
//        Button {
//            id: button
//            text: qsTr("добавить")
//            Layout.fillHeight: true

//            onClicked: {
//                listModel.append({ textList: textInput.text })
//            }
//        }

//        TextArea {
//            id: textArea
//            x: 81
//            y: 20
//            width: 100
//            height: 100
//            text: qsTr("t
//    e
//    s
//    t
//    ") }

        Button {
            id: button2
            text: qsTr("My")
            Layout.fillHeight: true

            onClicked: {
                listModel.append({ textList: textInput.text })
            }
        }

        Connections {
            target: button2
            onClicked: {
                //textArea.text = ''
                var xmlhttp = new XMLHttpRequest()
                var url = "http://www.evileg.ru/it_example.json"

                xmlhttp.onreadystatechange = function () {
                    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                        print(xmlhttp.responseText)
                        myFunction(xmlhttp.responseText)
                    }
                }
                xmlhttp.open("GET", url, true)
                //xmlhttp.setRequestHeader('Authorization', 'Basic Q1hLRURwNXA2cW1NUk1nVU9HZHgyUHdIYVlyRTIwa3Y6');
                xmlhttp.send()

                function myFunction(json) {
                    var obj = JSON.parse(json)
                    console.log(xmlhttp.responseText)

                    console.log('start loop' + obj.employees.length)

                    //                print({
                    //                          "jsondata": obj.items[''].nome
                    //                      })
                    var i = 0
                    for (i; i < obj.employees.length; i++) {
                        //ListModel.firstName=obj.employees[i].firstName
                        //fruitModel.model.append({
                        //                            "jsondata": obj.employees[i].firstName
                        //                        })
                        console.log('i=' + i)
                        console.log(obj.employees[i].firstName)
                        console.log('count list view =' + ListModel.count)
                       // ListModel. append({firstName: obj.employees[i].firstName, lastName: obj.employees[i].lastName })
                        listModel.append({ textList: obj.employees[i].firstName + ' -> ' + obj.employees[i].lastName })
                        //textArea.text = textArea.text + obj.employees[i].firstName + '\n'
                    }
                }
                button.text = 'done'
                //print('count is ' + listView.count)"
                //listView.view.red
                console.log('delegate')
                //ListView.delegate = obj.employees
                //print(listView.model)
                //listView.positionViewAtIndex(listView.count - 1, ListView.End)
                //print(listView.preferredHighlightBegin)
                print("clicked1")
                print("clicked2")
            }
        }


    }

    // Список, в который добавляются элементы с данными из TextInput
    ListView {
        id: listView

        anchors.top: rowLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        z: 1 // Расположение ниже, чем слой с TextInput и Button

        // Описание внешнего вида одного элемента в ListView
        delegate: Text {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: textList // Роль свойства text, в которую будут передаваться данные
        }


        // Модель для представления данных в ListView
        model: ListModel {
            id: listModel
        }
    }
}

