#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "bcdevice.h"
#include <QObject>
#include <QQmlContext>
#include <QThread>
#include "mainmodel.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //QThread workerThread;
    //BcDevice::Instance()->moveToThread(&workerThread);
    //QMetaObject::invokeMethod(BcDevice::Instance(), "openFromSerialNum", Qt::QueuedConnection, Q_ARG(QString, "497713873933"), Q_ARG(quint32, 115200));

    MainModel mainModel;
    engine.rootContext()->setContextProperty("MainModel", &mainModel);
    QObject::connect(BcDevice::Instance(), &BcDevice::sendNewData, &mainModel, &MainModel::getNewData);




    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    //BcDevice::Instance()->printSerialInfo();
    //BcDevice::Instance()->openFromSerialNum("497713873933", 115200);



    return app.exec();
}
