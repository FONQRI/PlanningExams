#include <CPP/planmanager.h>
#include <CPP/programmer.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <fstream>   // std::ofstream
#include <iostream>  //std::clog
#ifdef _DEBUG
const bool is_debig = true;
#else
const bool is_debig = false;
#endif
int main(int argc, char *argv[])
{
	if (!is_debig)
	{
		std::ofstream nullstream;
		std::clog.rdbuf(nullstream.rdbuf());
	}

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
