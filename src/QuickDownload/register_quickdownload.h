#ifndef REGISTER_QUICKDOWNLOAD_H
#define REGISTER_QUICKDOWNLOAD_H

#include <QtDebug>
#include <QtCore/QCoreApplication>
#include <QtQml/QQmlEngine>

#include "src/quickdownload.h"

static void registerQuickDownload() {
    qDebug() << "register quick download";
    qmlRegisterType<QuickDownload>("com.blackgrain.qml.quickdownload", 1, 0, "Download");
}

Q_COREAPP_STARTUP_FUNCTION(registerQuickDownload)

#endif // REGISTER_QUICKDOWNLOAD_H
