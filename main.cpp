#include <CPP/planmanager.h>
#include <CPP/programmer.h>
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
    engine.rootContext()->setContextProperty("PlanModel", P.getModel());
    engine.load(QUrl(QLatin1String("qrc:/QML/main.qml")));
    Programmer programmer;
    return app.exec();
}
