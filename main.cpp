#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QQmlContext>
#include <QQuickWindow>
#include "basic/KxUtils.h"
#include "basic/KxSystemTray.h"
#include "basic/KxFileSearch.h"
#include "basic/KxBluetooth.h"
#include "basic/KxDesktopServices.h"
#include "basic/KxFileContent.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("vlink");
    QApplication::setOrganizationName("kxtry");
    QApplication::setOrganizationDomain("kxtry.com");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QString lang = QLocale::system().name();
    QTranslator translator;
    if (translator.load("i18n_" + QLocale::system().name(), ":/i18n/")) {
        QCoreApplication::installTranslator(&translator);
    }

    KxUtils utils;
    KxSystemTray tray;

    qmlRegisterType<KxFileContent>("KxFileContent", 1,0, "KxFileContent");
    qmlRegisterType<KxFileSearch>("KxFileSearch", 1,0, "KxFileSearch");
    qmlRegisterType<KxBluetooth>("KxBluetooth", 1,0, "KxBluetooth");
    qmlRegisterType<KxDesktopServices>("KxDesktopServices", 1,0, "KxDesktopServices");

    QQmlApplicationEngine engine;
    QQmlContext *qmlContext = engine.rootContext();
    qmlContext->setContextProperty("KxUtils", &utils);
    qmlContext->setContextProperty("KxSystemTray", &tray);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QQuickWindow *appWindow = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    qmlContext->setContextProperty("appWindow", appWindow);
    qDebug() << "surfaceType:" << appWindow->surfaceType();
    return app.exec();
}
