function hash_set(hashtxt)
{
    console.log('globalForJs=' + globalHash);
    if (hashtxt == '' | hashtxt == null) return globalHash;
    globalHash=hashtxt
    return globalHash;
}
function myFunction(json) {



    //console.log(xmlhttp.responseText)
    console.log(json)
    var obj = JSON.parse(json)
    console.log(obj.versions[0].appver)

    console.log('start loop' + obj.versions.length)

    //                print({
    //                          "jsondata": obj.items[''].nome
    //                      })
    var i = 0
    textArea2.text = ''
    downurl.text = ''
    for (i; i < obj.versions.length; i++) {
        //ListModel.firstName=obj.employees[i].firstName
        //fruitModel.model.append({
        //                            "jsondata": obj.employees[i].firstName
        //                        })
        console.log('i=' + i)
        console.log(obj.versions[i].appver)
        console.log(obj.versions[i].changesTxt)
        console.log(obj.versions[i].hashsum)
        hash_set(obj.versions[i].hashsum)
        textArea.text = textArea.text + obj.versions[i].appver
                + ' -- ' + obj.versions[i].changesTxt + '\n'
        if (textAreaVer.text == obj.versions[i].appver) {
            //     textArea2.text = textArea2.text + obj.versions[i].appver
            //             + ' its current version i=' + i + '\n'
            console.log(obj.versions[i].appver + ' its current version i=' + i)
        }

        if (obj.versions[i].appver < textAreaVer.text) {
            // textArea2.text = textArea2.text + obj.versions[i].appver
            //        + ' its lover version version i=' + i + '\n'
            console.log(obj.versions[i].appver + ' its lover version i=' + i)
            //button.text = 'Нет обновлений'
        }

        if (obj.versions[i].appver > textAreaVer.text) {
            textArea2.text = textArea2.text + obj.versions[i].appver
                    + ' - ' + obj.versions[i].changesTxt + '\n'
            console.log(obj.versions[i].appver + ' its upper version i=' + i)
//            downurl.text = downurl.text + "Скачать " + obj.versions[i].appver + ' '
//                    + "<a href=\"https://github.com/" + "fly" + "true" + "/dev-"
//                    + "apk1/releases/download/" + obj.versions[i].appver
//                    + "/dev-preview.apk" + "\">версию</a><br>\n"
            download2.url = "https://github.com/" + "fly" + "true" + "/dev-"
                                + "apk1/releases/download/" + obj.versions[i].appver
                                + "/dev-preview.apk"
            //button.text = 'Update aviable'
        }
        //popuptxt.text = popuptxt.text + downurl.text
    }
}


function myCheckupdate()
{
console.log('check update function start')
var xmlhttp = new XMLHttpRequest()
var url = "https://raw.githubusercontent.com/" + "fly" + "true"
        + "/dev-" + "apk1/master/binapk/version.json"
console.log(url)
xmlhttp.onreadystatechange = function () {
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        print('result download is')
        print(xmlhttp.responseText)
        myFunction(xmlhttp.responseText)
    }
}
xmlhttp.open("GET", url, true)
//xmlhttp.setRequestHeader('Authorization', 'Basic Q1hLRURwNXA2cW1NUk1nVU9HZHgyUHdIYVlyRTIwa3Y6');
xmlhttp.send()
}

