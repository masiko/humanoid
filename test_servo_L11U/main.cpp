#include "Servo_Control.h"
DigitalOut L(LED3);

int main(){
	L = 1;
    ServoControl s9(p9);
    ServoControl s10(p10);
    ServoControl s11(p11);
    ServoControl s12(p12);
    ServoControl s13(p13);
    ServoControl s14(p14);
    ServoControl s15(p15);
    ServoControl s16(p16);
    ServoControl s17(p17);
    ServoControl s18(p18);
    ServoControl s19(p19);
    ServoControl s20(p20);
	wait(1);
    while(1){
		s9.setPos(1400);
		s10.setPos(1400);
		s11.setPos(1400);
		s12.setPos(1400);
		s13.setPos(1400);
		s14.setPos(1400);
		s15.setPos(1400);
		s16.setPos(1400);
		s17.setPos(1400);
		s18.setPos(1400);
		s19.setPos(1400);
		s20.setPos(1400);
//		wait(0.025);
		wait_ms(5);
		L = 0;
		s9.setPos(1600);
		s10.setPos(1600);
		s11.setPos(1600);
		s12.setPos(1600);
		s13.setPos(1600);
		s14.setPos(1600);
		s15.setPos(1600);
		s16.setPos(1600);
		s17.setPos(1600);
		s18.setPos(1600);
		s19.setPos(1600);
		s20.setPos(1600);
//		wait(0.025);
		wait_ms(5);
		L = 1;
    }
    return 0;
}
