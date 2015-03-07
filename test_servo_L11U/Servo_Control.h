#include "mbed.h"

class ServoControl{
private:
    DigitalOut _pin;
    Ticker tic;
	int power;
    int pos;
    float width;
public:
    ServoControl(PinName pin);
    ServoControl(PinName pin, int init_ang);
    ~ServoControl();
	int setPower(int);
    int setPos(int);
    int setPulseWidth(int);
    void setPulse();
};

