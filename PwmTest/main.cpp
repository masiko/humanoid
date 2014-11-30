#include "mbed.h"

Ticker servo2;
Ticker servo3;
Ticker servo4;
Ticker servo5;
DigitalOut pin5(p5);
DigitalOut pin7(p7);
DigitalOut pin9(p9);
DigitalOut pin11(p11);
PwmOut pin21(p21);
PwmOut pin22(p22);
PwmOut pin23(p23);
PwmOut pin24(p24);
PwmOut pin25(p25);
PwmOut pin26(p26);

void setPos2(){
	pin5 = 1;
	wait_us(1500);
	pin5 = 0;
}

void setPos3(){
	pin7 = 1;
	wait_us(1500);
	pin7 = 0;
}

void setPos4(){
	pin9 = 1;
	wait_us(1500);
	pin9 = 0;
}

void setPos5(){
	pin11 = 1;
	wait_us(1500);
	pin11 = 0;
}

int main(){
	pin21.period_ms(20);
	pin21.pulsewidth_us(1500);
	pin22.period_ms(20);
	pin22.pulsewidth_us(1500);
	pin23.period_ms(20);
	pin23.pulsewidth_us(1500);
	pin24.period_ms(20);
	pin24.pulsewidth_us(1500);
	pin25.period_ms(20);
	pin25.pulsewidth_us(1500);
	pin26.period_ms(20);
	pin26.pulsewidth_us(1500);
	servo2.attach(&setPos2, 0.02);
	servo3.attach(&setPos3, 0.02);
	servo4.attach(&setPos4, 0.02);
	servo5.attach(&setPos5, 0.02);

	while(1){
		wait(1.0);
	}
	return 0;
}
