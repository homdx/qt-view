#include "langswitch.h"
#include <QtDebug>


LangSwitch::LangSwitch(QObject *parent) :
    QObject(parent)
{
}

QString LangSwitch::userName()
{
    return m_userName;
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
