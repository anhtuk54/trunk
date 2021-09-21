#include "CApp.h"

CApp::CApp(int ac, char **av, QObject *parent) : QObject(parent)
{
    _guiApp = new QGuiApplication(ac,av);
    _engine = new QQmlApplicationEngine;


    // Logic Binding
    QObject::connect(&_uimodel, &CUIModel::isRunningChanged,
                     &_commander, &CCommander::onRunningStateChanged);
    QObject::connect(&_uimodel, &CUIModel::speedChanged,
                     &_commander, &CCommander::onSpeedChanged);

    // UI Binding
    _engine->rootContext()->setContextProperty("CUIModel",&_uimodel);


    // UI Loading
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(_engine, &QQmlApplicationEngine::objectCreated,
                     _guiApp, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    _engine->load(url);
}

int CApp::exec()
{
    if (_guiApp) {
        return _guiApp->exec();
    }
    else {
        return EXIT_FAILURE;
    }
}
