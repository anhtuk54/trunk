#ifndef CAPP_H
#define CAPP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QPointer>
#include <QSharedPointer>

#include "CUIModel.h"
#include "CCommander.h"

class CApp : public QObject
{
    Q_OBJECT
public:
    explicit CApp(int ac, char **av, QObject *parent = nullptr);
    int exec();

signals:


private:
    QPointer<QGuiApplication> _guiApp;
    QPointer<QQmlApplicationEngine> _engine;
    CUIModel _uimodel;
    CCommander _commander;
};

#endif // CAPP_H
