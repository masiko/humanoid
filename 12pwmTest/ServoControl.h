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

ServoControl::ServoControl(PinName pin) : _pin(pin) {
	pos = 1500;
	width = 0.02;
	tic.attach(this, &ServoControl::setPulse, width);
}

ServoControl::~ServoControl(){};

int ServoControl::setPos(int input){
	if (input<900 || 2100<input)	return 1;
	pos = input;
	return 0;
}

int ServoControl::setPulseWidth(int input){
	if (input<16 || 24<input)	return 1;
	width = (float)input/1000.0;
	return 0;
}

void ServoControl::setPulse(){
	_pin = 1;
	wait_us(pos);
	_pin = 0;
}

