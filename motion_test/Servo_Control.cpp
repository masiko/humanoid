#include "Servo_Control.h"

ServoControl::ServoControl(PinName pin) : _pin(pin) {
    pos = 1500;
    width = 0.02;
	power = 0;
//    tic.attach(this, &ServoControl::setPulse, width);
}

ServoControl::~ServoControl(){};

int ServoControl::setPower(int sw) {
	if (!power && sw)	power = 1, tic.attach(this, &ServoControl::setPulse, width);
	else if (power && !sw)	power = 0, tic.detach();
	return 0;
}

int ServoControl::setPos(int input) {
    if (input<700 || 2300<input)    return 1;
    pos = input;
    return 0;
}

int ServoControl::setPulseWidth(int input){
    if (input<16 || 24<input)   return 1;
    width = (float)input/1000.0;
    return 0;
}

void ServoControl::setPulse(){
    _pin = 1;
    wait_us(pos);
    _pin = 0;
}

