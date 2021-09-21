#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

class CommandInterface
{
public:
    virtual int start()=0;
    virtual int stop()=0;
    virtual int changeSpeed(const int& speed)=0;
};

#endif // COMMANDINTERFACE_H
