#ifndef CUIMODEL_H
#define CUIMODEL_H

#include <QObject>

class CUIModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
public:
    explicit CUIModel(QObject *parent = nullptr);

    bool isRunning() const;
    void setIsRunning(const bool &state);

    int speed() const;
    void setSpeed(const int &val);

signals:
    void isRunningChanged(const bool &state);
    void speedChanged(const int &val);

private:
    bool _isRunning;
    int _speed;
};

#endif // CUIMODEL_H
