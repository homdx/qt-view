function load() {

    if (pageLoader.status == Loader.Ready) {
                                 console.log('Loaded from url');
                                statusline.text = 'Download ok';
                             } else
                             {
                                 statusline.text = 'error download from url';
                                 console.log('error loading. local run');

                                 //statuslinetimer.stop()
                                 //statuslinetimer.start()
                                 pageLoader.source = "Page1Form.ui.qml";
                             }
        }
