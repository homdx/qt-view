#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>


#include <QtDebug>
#include <QTranslator>

#include <QtGui>
#include "langswitch.h"
#include "QuickDownload/src/quickdownload.h"
#include "langswitch.h"

#include "applicationui.hpp"

int main(int argc, char *argv[])
{

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qputenv("QT_QUICK_CONTROLS_STYLE", "material");
    QGuiApplication app(argc, argv);
    ApplicationUI appui;

    QQmlApplicationEngine engine;

    // from QML we have access to ApplicationUI as myApp
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("myApp", &appui);
    // some more context properties
    appui.addContextProperty(context);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qDebug() << "before" << QLocale().name();

#if defined(Q_OS_ANDROID)
    QObject::connect(&app, SIGNAL(applicationStateChanged(Qt::ApplicationState)), &appui, SLOT(onApplicationStateChanged(Qt::ApplicationState)));
#endif

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
