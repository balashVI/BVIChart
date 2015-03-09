#include <QApplication>
#include <QQmlApplicationEngine>
#include "../src/charts_plugin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChartsPlugin plugins;
    plugins.registerTypes("BVI.Charts");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
