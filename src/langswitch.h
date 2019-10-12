#ifndef LANGSWITCH_H
#define LANGSWITCH_H

#include <QObject>

class LangSwitch: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    //Q_PROPERTY(QString appPath READ getAppPath WRITE setAppPath)
    Q_PROPERTY(bool requestPermissions READ requestPermissions)
    //Q_PROPERTY(QString getAppPath READ getAppPath WRITE setAppPath)
    Q_PROPERTY(QString setAppPath WRITE setAppPath)
    Q_PROPERTY(QString getnewAppPath READ getnewAppPath)
    //Q_PROPERTY(bool copyFile READ copyFile)
    //Q_PROPERTY(QString setSourceFile WRITE setSourceFile)
    //Q_PROPERTY(QString setDestFile WRITE setDestFile)
    Q_PROPERTY(QString setSourceFile WRITE setSourceFile)// NOTIFY sourceFileChanged)
    Q_PROPERTY(QString setDestFile WRITE setDestFile)// NOTIFY destFileChanged)

public:
    explicit LangSwitch(QObject *parent = nullptr);
Q_INVOKABLE bool copyFile2(const QString &source, const QString &dist);
    QString userName();
    QString getAppPath();
    QString getnewAppPath();
    void InstallApp(const QString &appPackageName);
    QString setAppPath(const QString &appPathChange);
    void setUserName(const QString &userName);
    bool requestPermissions();
    void setSourceFile(const QString &sourceFile);
    void setDestFile(const QString &destFile);
    //bool copyFile2(const QString &soure, QString &destination);
    //

signals:
    void userNameChanged();

private:
    QString m_userName;
    QString m_appPath;
    QString mDataPath;
    QString m_sourcefile;
    QString m_destfile;
    bool copyFile();
    bool checkDirs();
};

#endif // LANGSWITCH_H
