#include "Servo_Control.h"
DigitalOut L(LED3);

int main(){
	int ang1 = 1500;
	int da = 30, a = 30;
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
		if (ang1 >= 1850)	da = -a;
		else if (ang1 <=1250)	da = a;
		ang1 += da;

		s9.setPos(ang1);
		s10.setPos(ang1);
		s11.setPos(ang1);
		s12.setPos(ang1);
		s13.setPos(ang1);
		s14.setPos(ang1);
		s15.setPos(ang1);
		s16.setPos(ang1*2);
		s17.setPos(ang1);
		s18.setPos(ang1);
		s19.setPos(ang1);
		s20.setPos(ang1);
		wait_ms(20);
		L = L ? 0 : 1;
    }
    return 0;
}
