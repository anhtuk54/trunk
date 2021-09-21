#include "CCommander.h"
#include <QDebug>

CCommander::CCommander(QObject *parent)
    : QObject(parent)
{
}

void CCommander::onRunningStateChanged(const bool &state)
{
    qDebug() << __FUNCTION__ << state;

    if (nullptr == _iface) return;

    if (state) {
        _iface->start();
    }
    else {
        _iface->stop();
    }
}

void CCommander::onSpeedChanged(const int &speed)
{
    qDebug() << __FUNCTION__ << speed;

    if (nullptr == _iface) return;

    _iface->changeSpeed(speed);
}
