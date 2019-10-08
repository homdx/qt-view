#ifndef LANGSWITCH_H
#define LANGSWITCH_H

#include <QObject>

class LangSwitch: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    //Q_PROPERTY(QString appPath READ getAppPath WRITE setAppPath)
    Q_PROPERTY(QString requestPermissions READ requestPermissions)
    //Q_PROPERTY(QString getAppPath READ getAppPath WRITE setAppPath)
    Q_PROPERTY(QString setAppPath WRITE setAppPath)
    Q_PROPERTY(QString getnewAppPath READ getnewAppPath)

public:
    explicit LangSwitch(QObject *parent = nullptr);

    QString userName();
    QString getAppPath();
    QString getnewAppPath();
    void InstallApp(const QString &appPackageName);
    QString setAppPath(const QString &appPathChange);
    void setUserName(const QString &userName);
    bool requestPermissions();

signals:
    void userNameChanged();

private:
    QString m_userName;
    QString m_appPath;
    QString mDataPath;
    bool checkDirs();
};

#endif // LANGSWITCH_H
