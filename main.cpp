#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include "src/systemtray.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QString lang = QLocale::system().name();
    QTranslator translator;
    if (translator.load("i18n_" + QLocale::system().name(), ":/res/i18n/")) {
        QCoreApplication::installTranslator(&translator);
    }

    SystemTray tray;
    tray.showSplash();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
