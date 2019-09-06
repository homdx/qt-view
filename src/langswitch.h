#ifndef LANGSWITCH_H
#define LANGSWITCH_H

#include <QObject>

class LangSwitch: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)

public:
    explicit LangSwitch(QObject *parent = nullptr);

    QString userName();
    void setUserName(const QString &userName);

signals:
    void userNameChanged();

private:
    QString m_userName;
};

#endif // LANGSWITCH_H
