#include <CPP/planmanager.h>
#include <CPP/programmer.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    PlanManager PM;
    Programmer P(PM.getPlansList(), PM.getQuery());
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("PlanManager", &PM);
    engine.rootContext()->setContextProperty("Programmer", &P);
    engine.rootContext()->setContextProperty("PlanModel", PM.getModel());
    engine.load(QUrl(QLatin1String("qrc:/QML/main.qml")));
    return app.exec();
}
