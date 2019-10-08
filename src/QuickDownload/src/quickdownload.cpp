#include "QuickDownload/src/quickdownload.h"
#include <QtDebug>

#if defined(QUICKDOWNLOAD_AUTO_REGISTER)
#include "register_quickdownload.h"
#endif

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
const static char* MY_JAVA_CLASS = "org.qtproject.qtdownlod2/AndroidIntentLauncher";
#endif /* Q_OS_ANDROID */

QuickDownloadMaster *QuickDownloadMaster::self = 0;

QuickDownloadMaster::QuickDownloadMaster(QObject *parent):
    QObject(parent)
{
    _ready = false;
    qDebug() << "DEBUGTXT QuickDownloadMaster";
    Q_ASSERT_X(!self, "QuickDownloadMaster", "there should be only one instance of this object");
    QuickDownloadMaster::self = this;

    _networkAccessManager = 0;
    _ownNetworkAccessManager = false;

    _ready = true;
    emit readyChanged();
}

QuickDownloadMaster::~QuickDownloadMaster()
{
    qDebug() << "DEBUGTXT ~QuickDownloadMaster";
    if(_ownNetworkAccessManager) {
        delete _networkAccessManager;
        _networkAccessManager = 0;
    }
}

QuickDownloadMaster *QuickDownloadMaster::instance()
{
    qDebug() << "DEBUGTXT instance";
   if(self == 0)
       self = new QuickDownloadMaster(0);
   return self;
}

bool QuickDownloadMaster::ready()
{
    qDebug() << "DEBUGTXT ready";
    return _ready;
}

bool QuickDownloadMaster::checkInstance(const char *function)
{
    bool b = (QuickDownloadMaster::self != 0);
    qDebug() << "DEBUGTXT checkInstance";
    if (!b)
        qWarning("QuickDownloadMaster::%s: Please instantiate the QuickDownloadMaster object first", function);
    return b;
}


QNetworkAccessManager *QuickDownloadMaster::networkAccessManager()
{
    qDebug() << "DEBUGTXT networkAccessManager";
    if(_networkAccessManager == 0) {
        _networkAccessManager = new QNetworkAccessManager(self);
        _ownNetworkAccessManager = true;
    }
    return _networkAccessManager;
}

void QuickDownloadMaster::setNetworkAccessManager(QNetworkAccessManager *networkAccessManager)
{
    qDebug() << "DEBUGTXT setNetworkAccessManager";
    if(_ownNetworkAccessManager && _networkAccessManager) {
        delete _networkAccessManager;
        _networkAccessManager = 0;
        _ownNetworkAccessManager = false;
    }
    _networkAccessManager = networkAccessManager;
}

/*
 * QuickDownload
 */
QuickDownload::QuickDownload(QObject *parent):
    QObject(parent)
{
    qDebug() << "DEBUGTXT QuickDownload";
    _networkReply = nullptr;
    _saveFile = nullptr;
    _componentComplete = false;
    _running = false;
    _overwrite = false;
    _progress = 0.0;
    _followRedirects = false;
}

QuickDownload::~QuickDownload()
{
    qDebug() << "DEBUGTXT ~QuickDownload";
    if(_networkReply) {
        if(_networkReply->isRunning())
            _networkReply->abort();
        shutdownNetworkReply();
    }

    if(_saveFile) {
        _saveFile->cancelWriting();
        shutdownSaveFile();
    }
}

QUrl QuickDownload::url() const
{
    qDebug() << "DEBUGTXT url";
    return _url;
}

void QuickDownload::setUrl(const QUrl &url)
{
    qDebug() << "DEBUGTXT setUrl " << url;
    if(_url != url) {
        _url = url;
        emit urlChanged();
    }
}


void QuickDownload::InstallApp(const QString &appPackageName) {

     qDebug() << "DEBUGTXT InstallApp java ";
#ifdef Q_OS_ANDROID



        QAndroidJniObject jsText = QAndroidJniObject::fromString(appPackageName);
        QAndroidJniObject::callStaticMethod<jint>(MY_JAVA_CLASS,
                                           "installApp",
                                           "(Ljava/lang/String;)I",
                                           jsText.object<jstring>());
        #endif /* Q_OS_ANDROID */
        qDebug() << "DEBUGTXT InstallApp java done ";
   }

void QuickDownload::setHashSum(const QByteArray &hashsum)
{
    qDebug() << "DEBUGTXT setHashSum " << hashsum;
    _setHashSum = hashsum;

}

bool QuickDownload::running() const
{
    qDebug() << "DEBUGTXT running";
    return _running;
}

void QuickDownload::setRunning(bool running)
{
    qDebug() << "DEBUGTXT setRunning";
    if(_running != running) {
        _running = running;
        if(!_running) {

            if(_networkReply) {
                if(_networkReply->isRunning())
                    _networkReply->abort();
                shutdownNetworkReply();
            }

            if(_saveFile) {
                _saveFile->cancelWriting();
                shutdownSaveFile();
            }
        } else
            start();

        emit runningChanged();
    }

}

qreal QuickDownload::progress() const
{
    qDebug() << "DEBUGTXT progress";
    return _progress;
}

QUrl QuickDownload::destination() const
{
    qDebug() << "DEBUGTXT destination";
    return _destination;
}

void QuickDownload::setDestination(const QUrl &destination)
{
    qDebug() << "DEBUGTXT setDestination";
    if(_destination != destination) {
        _destination = destination;
        if(_saveFile && !_running) {
            QString newDestination = _destination.toDisplayString(QUrl::PreferLocalFile);
            if(_saveFile->fileName() != newDestination)
                _saveFile->setFileName(newDestination);
            qDebug() <<  "DEBUGTXT setDestination filenameis file =" << _saveFile->fileName();
        }
        emit destinationChanged();
    }
}

bool QuickDownload::followRedirects() const
{
    qDebug() << "DEBUGTXT followRedirects";
    return _followRedirects;
}

void QuickDownload::setFollowRedirects(bool followRedirects)
{
    qDebug() << "DEBUGTXT setFollowRedirects";
    if(_followRedirects != followRedirects) {
        _followRedirects = followRedirects;
        emit followRedirectsChanged();
    }
}

void QuickDownload::componentComplete()
{
    qDebug() << "DEBUGTXT componentComplete";
    _componentComplete = true;
    if(_running)
        start();
}

void QuickDownload::start(QUrl url)
{
    qDebug() << "DEBUGTXT start";
    if(!_componentComplete)
        return;

    if(url.isEmpty()) {
        emit error(Error::ErrorUrl,"Url is empty");
        return;
    }

    if(_destination.isEmpty()) {
        emit error(Error::ErrorDestination,"Destination is empty");
        return;
    }

    qDebug() << "DEBUGTXT before setup qUrl is " << url;
    //qDebug() << remove_qrc(url);
    //qDebug() << "DEBUGTXT now start setup url ";
    //setUrl(remove_qrc(url));
    setUrl(url);

    QString destination = _destination.toDisplayString(QUrl::PreferLocalFile);

    if (QFile::exists(destination)) {
        if(!_overwrite) {
            emit error(Error::ErrorDestination,"Overwriting not allowed for destination file \""+destination+"\"");
            return;
        }
    }

    // Cancel and delete any previous open _saveFile disregarding it's state
    if(_saveFile)
        _saveFile->cancelWriting();
    shutdownSaveFile();
    qDebug() << "DEBUGTXT destination file is " << destination;
    qDebug() << "DEBUGTXT new destination file is " << remove_qrc(destination);
    _saveFile = new QSaveFile(remove_qrc(destination));

    if (!_saveFile->open(QIODevice::WriteOnly)) {
        emit error(Error::ErrorDestination,_saveFile->errorString());
        shutdownSaveFile();
        return;
    }

    // Shutdown any previous used replies
    shutdownNetworkReply();
    _networkReply = qQuickDownloadMaster->networkAccessManager()->get(QNetworkRequest(_url));

    connect(_networkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_networkReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
    connect(_networkReply, SIGNAL(finished()), this, SLOT(onFinished()));

    setProgress(0.0);
    setRunning(true);
    emit started();
}

QString QuickDownload::remove_qrc(QString url) {
    //QString host = url.fileName();
       if (url.length()>4) {
    if (url.startsWith("qrc:"))
    {
        qDebug() << "DEBUGTXT remove qrc from url";
        url = url.mid(4); // = remove first 4 chars
        qDebug() << "DEBUGTXT result qrc is " << url;
       }
}
   if (url.length()>7) {
    if (url.startsWith("file://"))
    {
        qDebug() << "DEBUGTXT remove file:/// from url";
        url = url.mid(7); // = remove first 4 chars
        qDebug() << "DEBUGTXT result file:/// is " << url;
       }
   }
    return url;

}

void QuickDownload::start()
{
    qDebug() << "DEBUGTXT start";
    start(_url);
}

void QuickDownload::stop()
{
    qDebug() << "DEBUGTXT stop";
    setRunning(false);
}

void QuickDownload::onReadyRead()
{
    qDebug() << "DEBUGTXT onReadyRead";
    if (_saveFile)
        _saveFile->write(_networkReply->readAll());
}

void QuickDownload::onFinished()
{
    qDebug() << "DEBUGTXT componentComplete";
    if (!_running) {
        if(_saveFile)
            _saveFile->cancelWriting();
    }
    if(!_networkReply) {
        emit error(Error::ErrorNetwork,"Network reply was deleted");
        if(_saveFile)
            _saveFile->cancelWriting();
        shutdownSaveFile();
        return;
    }

    // get redirection url
    QVariant redirectionTarget = _networkReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (_networkReply->error()) {
        _saveFile->cancelWriting();
        emit error(Error::ErrorNetwork,_networkReply->errorString());
    } else if (!redirectionTarget.isNull()) {
        QUrl newUrl = _url.resolved(redirectionTarget.toUrl());

        emit redirected(newUrl);

        if(_followRedirects) {

            start(newUrl);
            return;
        } else {
            emit error(Error::ErrorNetwork,"Re-directs not allowed");
        }
    } else {
        if(_saveFile->commit()) {
            shutdownSaveFile();
            setProgress(1.0);
            setRunning(false);
            emit finished();
        } else {
            if(_saveFile)
                _saveFile->cancelWriting();
            emit error(Error::ErrorDestination,"Error while writing \""+_destination.toDisplayString(QUrl::PreferLocalFile)+"\"");
        }
    }

    shutdownNetworkReply();
    shutdownSaveFile();
}

void QuickDownload::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << "DEBUGTXT onDownloadProgress";
    if(!_running)
        return;
    emit update((bytesReceived / 1000), (bytesTotal / 1000));
    setProgress(((qreal)bytesReceived / bytesTotal));
}

void QuickDownload::setProgress(qreal progress)
{
    qDebug() << "DEBUGTXT setProgress";
    if(_progress != progress) {
        _progress = progress;
        emit progressChanged();
    }
}

bool QuickDownload::overwrite() const
{
    qDebug() << "DEBUGTXT overwrite";
    return _overwrite;
}

void QuickDownload::setOverwrite(bool allowOverwrite)
{
    qDebug() << "DEBUGTXT setOverwrite";
    if(_overwrite != allowOverwrite) {
        _overwrite = allowOverwrite;
        emit overwriteChanged();
    }
}

void QuickDownload::shutdownNetworkReply()
{
    qDebug() << "DEBUGTXT shutdownNetworkReply";
    if(_networkReply) {
        disconnect(_networkReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        disconnect(_networkReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
        disconnect(_networkReply, SIGNAL(finished()), this, SLOT(onFinished()));

        _networkReply->deleteLater();
        _networkReply = 0;
    }
}

QByteArray QuickDownload::check_sum_file_sha512(const QString fileName)
{
    _getHashSum = check_sum_file(fileName,QCryptographicHash::Sha512);
    qDebug() << "DEBUGTXT check_sum_file_sha512 = " <<_getHashSum << " it is hash and file name is " << fileName ;
    return _getHashSum;
}

QByteArray QuickDownload::getHashSum() const
{
qDebug() << "DEBUGTXT getHashSum = " <<_getHashSum << " it is hash";
return _getHashSum;
}

QByteArray QuickDownload::check_sum_file(const QString fileName,
                        QCryptographicHash::Algorithm hashAlgorithm)
{
    qDebug() << "DEBUGTXT fileChecksum for file " << fileName << " remove qrc=" << remove_qrc(fileName) << " and algorithm " << hashAlgorithm << " is started  ";
    QFile f(remove_qrc(fileName));
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            qDebug() << "DEBUGTXT fileChecksum to HEX " << hash.result().toHex();
            return hash.result().toHex();
        }
    }
    return QByteArray();
}

void QuickDownload::shutdownSaveFile()
{
    qDebug() << "DEBUGTXT shutdownSaveFile";
    if(_saveFile) {
        qDebug() << "DEBUGTXT shutdownSaveFile=" << _saveFile->fileName();
        _saveFile->commit();
        qDebug() << "DEBUGTXT shutdownSaveFile commited";
        if (_setHashSum.isNull()) {
            qDebug() << "DEBUGTXT not defined HashSum for checking";
                }
        else
        {
            QByteArray result;
            result = check_sum_file(_saveFile->fileName(), QCryptographicHash::Sha512);
            //QString resulttxt = QTextCodec::codecForMib(1015)->toUnicode(result);
            qDebug() << "DEBUGTXT result of checking raw " << result;
            if ( _setHashSum == result ) {
                qDebug() << "DEBUGTXT checksum is passed OK))))))";
            }
            else
            {
                qDebug() << "DEBUGTXT checksum is NOT PASSED (((((";
            }
         // qDebug() << "DEBUGTXT result of checking is " << resulttxt;
        }
        //check_sum_file(_saveFile->fileName(), QCryptographicHash::Sha512);
        delete _saveFile;
        _saveFile = 0;
    }
}
