#include <CPP/planmanager.h>
#include <CPP/programmer.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    PlanManager PP;
    Programmer P(PP.getPlansList());
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("PlanManager", &PP);
    engine.rootContext()->setContextProperty("Programmer", &P);
    engine.rootContext()->setContextProperty("PlanModel", PP.getModel());
    engine.load(QUrl(QLatin1String("qrc:/QML/main.qml")));
    return app.exec();
}
