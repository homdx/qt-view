#include "langswitch.h"
#include <QtDebug>
#include <QtGui>
#include <QtCore>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>
#endif /* Q_OS_ANDROID */


LangSwitch::LangSwitch(QObject *parent) :
    QObject(parent)
{
}

QString LangSwitch::getnewAppPath()
{
    qDebug() << "started getNewAppPath cpp function";
    qDebug() << "App path : " << m_appPath;
    return m_appPath;
}

QString LangSwitch::getAppPath()
{
    qDebug() << "started getAppPath cpp function";
    qDebug() << "m_appPath path now is: " << m_appPath;
    QString AppPath = qApp->applicationDirPath();
    qDebug() << "App path : " << qApp->applicationDirPath();
    return AppPath;
}

QString LangSwitch::setAppPath(const QString &appPathChange)
{
    qDebug() << "started setAppPath cpp function";
    qDebug() << "App path now is: " << appPathChange;
    qDebug() << "Old path m_AppPath value is: " << appPathChange;
    m_appPath = appPathChange;
    //return m_appPath;
    checkDirs();
    qDebug() << "now create path for file " << mDataPath;
    QFile readFile(mDataPath+"/yourfile.txt");
    QFile file;
    if(!readFile.exists()) {
            qDebug() << "R0 file doesn't exist ";
            file.setFileName(mDataPath+"/yourfile.txt");
            qDebug() << "R0 file opened ";
            if (readFile.open(QIODevice::WriteOnly))
            {
                qDebug() << "R1 file opened for write and write ";
                readFile.write("Test file string\n");
                readFile.write("Test file string2");
                qDebug() << "R1 write file done";
                readFile.close();
                qDebug() << "R2 File closed";
            }

            //return nullptr;
        }
    qDebug() << "before error1";
        if (!readFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Couldn't open file";
            return nullptr;
        }
        qDebug() << "before error2";
        //if ((readFile.exists())&&(readFile.open(QIODevice::ReadOnly)))
        //{
            QString filedata;
            qDebug() << "R2 file opened for read";
            filedata=(readFile.readAll());
            qDebug() << "R2 file readed all";
            readFile.close();
            qDebug() << "R2 file closed";
            qDebug() << "R2 datafile " << filedata ;
            return filedata;
        //}

}

bool LangSwitch::checkDirs()
{
    // Android: HomeLocation works, iOS: not writable
    // Android: AppDataLocation works out of the box, iOS you must create the DIR first !!
    //QString mDataPath;
    mDataPath = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).value(0);
    qDebug() << "Data Path: " << mDataPath;
    QDir myDir(mDataPath);
    if (!myDir.exists()) {
        bool ok = myDir.mkpath(mDataPath);
        if(!ok) {
            qWarning() << "Couldn't create dir. " << mDataPath;
            return false;
        }
        qDebug() << "created directory path" << mDataPath;
    }
    return true;
}


QString LangSwitch::userName()
{
    return m_userName;
}

bool LangSwitch::requestPermissions()
{
    #ifdef Q_OS_ANDROID
    qDebug() << "requestPermissions - request permissions";
    QtAndroid::PermissionResult r = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    qDebug() << "requestPermissions - requested permissions";
    if(r == QtAndroid::PermissionResult::Denied) {
        QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
        r = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
        if(r == QtAndroid::PermissionResult::Denied) {
            qDebug() << "requestPermissions - storage is deny!!! permissions";
            return false;
        }
    }
    #endif
    qDebug() << "requestPermissions - allowed permissions";
    return true;
}

bool LangSwitch::copyFile2(const QString &sourceFile, const QString &destFile)
{

    if (sourceFile == nullptr || destFile == nullptr)
    {
        qDebug() << " one of parameter copy file is null ";
        return false;
    }
    if (sourceFile == destFile) {
     qDebug() << "source file = destination file" << sourceFile;
     return false;
    }

    if (QFile::exists(destFile))
    {
        qDebug() << "dest file is exist - remove it = " << destFile;
        QFile::remove(destFile);
    }
    qDebug() << "source file is " << sourceFile << " and destination is " << destFile;
    return QFile::copy(sourceFile, destFile);



}

bool LangSwitch::copyFile ()
{
    if (m_sourcefile == nullptr || m_destfile == nullptr)
    {
        qDebug() << " one of parameter copy file is null ";
        return false;
    }
    if (m_sourcefile == m_destfile) {
     qDebug() << "source file = destination file" << m_sourcefile;
     return false;
    }

    if (QFile::exists(m_destfile))
    {
        qDebug() << "dest file is exist - remove it = " << m_destfile;
        QFile::remove(m_destfile);
    }
    qDebug() << "source file is " << m_sourcefile << " and destination is " << m_destfile;
    return QFile::copy(m_sourcefile, m_destfile);

}

void LangSwitch::setSourceFile(const QString &sourceFile)
{
m_sourcefile = sourceFile;
qDebug() << "set source file=" << m_sourcefile;
return;
}

void LangSwitch::setDestFile(const QString &destFile)
{
m_destfile = destFile;
qDebug() << "set destfile file=" << m_destfile;
return;
}


void LangSwitch::setUserName(const QString &userName)
{
    qDebug() << userName;
    qDebug() << m_userName;


    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}
