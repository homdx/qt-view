#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtDebug>
#include <QTranslator>

#include <QtGui>
#include "langswitch.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qDebug() << "before" << QLocale().name();

    app.setOrganizationName("qt-stackview");
    app.setOrganizationDomain("qt-stackview.com");
    app.setApplicationName("Qt Stack View Application");
    app.setApplicationVersion(APP_VERSION);

    QSettings settings2("qt-stackview", "Qt Stack View Application");
    qDebug() << "read lang settings" << settings2.value("sel_language","en_US");

    QTranslator translator;
    app.installTranslator(&translator);

    //QLocale curLocale(QLocale("en_US"));

    QVariant value = settings2.value("sel_language","ru_RU");
    QString localstring;
    if (value.type() == QVariant::StringList) {
      localstring = value.toStringList().join(",");
    } else {
      localstring = value.toString();
    }

    QLocale curLocale(localstring);
    QLocale::setDefault(curLocale);

    translator.load(QString(":/qt-stackview_%1.qm").arg(QLocale().name()));

    qDebug() << "after" << QLocale().name();
    engine.load(url);
    qmlRegisterType<LangSwitch>("io.qt.examples.langswitch", 1, 0, "LangSwitch");
    return app.exec();
}
