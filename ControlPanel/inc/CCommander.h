#ifndef CCOMMANDER_H
#define CCOMMANDER_H

#include <QObject>
#include <memory>

#include "CommandInterface.h"

class CCommander : public QObject
{
    Q_OBJECT
public:
    explicit CCommander(QObject *parent = nullptr);

public slots:
    void onRunningStateChanged(const bool &state);
    void onSpeedChanged(const int &speed);

signals:

private:
    std::shared_ptr<CommandInterface> _iface;
};

#endif // CCOMMANDER_H
