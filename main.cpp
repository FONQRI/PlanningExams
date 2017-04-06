#include <CPP/planmanager.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    PlanManager P;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("PlanManager", &P);
    engine.rootContext()->setContextProperty("PlanModel", P.model());
    engine.load(QUrl(QLatin1String("qrc:/QML/main.qml")));

    return app.exec();
}
