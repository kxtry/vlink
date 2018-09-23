#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QQmlContext>
#include <QQuickWindow>
#include "basic/KxUtils.h"
#include "basic/KxSystemTray.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("vlink");
    QApplication::setOrganizationName("kxtry");
    QApplication::setOrganizationDomain("kxtry.com");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QString lang = QLocale::system().name();
    QTranslator translator;
    if (translator.load("i18n_" + QLocale::system().name(), ":/res/i18n/")) {
        QCoreApplication::installTranslator(&translator);
    }

    KxSystemTray tray;

    QQmlApplicationEngine engine;
    QQmlContext *qmlContext = engine.rootContext();
    qmlContext->setContextProperty("KxUtils", new KxUtils(qmlContext));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QQuickWindow *appWindow = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    qmlContext->setContextProperty("AppWindow", appWindow);

    return app.exec();
}
