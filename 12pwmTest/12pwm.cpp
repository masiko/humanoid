#include "mbed.h"
#include "ServoControl.h"
/*
class Softpwm{
public:
	Softpwm(PinName pin) : _pin(pin) {
		_pin = 0;
	}

	void setf(){
		_pin = 1;
		wait_us(1500);
		_pin = 0;
	}
private:
	DigitalOut _pin;
};

class Servo{
public:
	Servo(PinName pin) : _softpwm(pin) {
		ser.attach(&_softpwm, &Softpwm::setf, 0.2);
	}

private:
	Ticker ser;
	Softpwm _softpwm;
};


class ServoC{
public:
	ServoC(PinName pin): _pin(pin) {
		ser.attach(this, &ServoC::setf, 0.02);
	}

	void setf(){
		_pin = 1;
		wait_us(1500);
		_pin = 0;
	}
private:
	Ticker ser;
	DigitalOut _pin;
};
*/

int main(){
	ServoControl s5(p5);
	ServoControl s7(p7);
	ServoControl s9(p9);
	ServoControl s11(p11);
	ServoControl s13(p13);
	ServoControl s15(p15);
	ServoControl s17(p17);
	ServoControl s19(p19);
	ServoControl s21(p21);
	ServoControl s23(p23);
	ServoControl s25(p25);
	ServoControl s27(p27);
/*	s5.setPulseWidth(21);
	s5.setPos(1200);
	s9.setPulseWidth(21);
	s9.setPos(1200);
*/
	while(1){
		wait(1);
	}
	return 0;
}


