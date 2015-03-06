#include "mbed.h"

class ServoControl{
private:
    DigitalOut _pin;
    Ticker tic;
    int pos;
    float width;
public:
    ServoControl(PinName pin);
    ~ServoControl();
    int setPos(int);
    int setPulseWidth(int);
    void setPulse();
};

