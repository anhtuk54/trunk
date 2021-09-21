#include "CUIModel.h"

#include <QDebug>

CUIModel::CUIModel(QObject *parent)
    : QObject(parent)
    , _isRunning(false)
    , _speed(0)
{
}

bool CUIModel::isRunning() const
{
    return _isRunning;
}

void CUIModel::setIsRunning(const bool &state)
{
    if (state != _isRunning) {
        _isRunning = state;
        emit isRunningChanged(_isRunning);
    }
}

int CUIModel::speed() const
{
    return _speed;
}

void CUIModel::setSpeed(const int &val)
{
    if(val != _speed) {
        _speed = val;
        emit speedChanged(_speed);
    }
}


