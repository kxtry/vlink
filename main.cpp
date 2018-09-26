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
#include "basic/KxRegexp.h"

#include <QRegExp>
#include <QDebug>

void test()
{
    {
        QRegExp rx("Host\\s([^\\r|\\n]*)");
        QStringList list;
        int pos = 0;
        KxFileContent fc;
        fc.setFileName("H:\\tools\\kxtry\\myssh\\config");
        QString str = fc.getContent();
        rx.indexIn(str);
        QStringList oks = rx.capturedTexts();
        qDebug() << "oks:" << oks;
        //str = "Host a2\r\nHost b2\r\nHost c3";
        while ((pos = rx.indexIn(str, pos)) != -1) {
              list << rx.cap(1);
              pos += rx.matchedLength();
        }
        qDebug() << "list:" << list;
    }
    exit(0);
}

void test2()
{
    KxRegexp rx;
    rx.setPattern("Host\\s([^\\r|\\n]*)");
    QStringList cts = rx.capturedTexts("Host a2\r\nHost b2\r\nHost c3");
    qDebug() << "cts:" << cts;
    exit(0);
}

int main(int argc, char *argv[])
{
    //test2();
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

    qmlRegisterType<KxRegexp>("KxRegexp", 1,0, "KxRegexp");
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
