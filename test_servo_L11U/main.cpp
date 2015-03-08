#include <stdio.h>
#include "Servo_Control.h"

Serial pc(USBTX, USBRX);
DigitalOut L(LED3);
LocalFileSystem local("local");

int main(){
	FILE *fp = fopen("/local/offset_a.txt","r");
	if (fp==NULL) return 1;
	int ang0 = 1500;
	int diff = 700;
	int tarpos = 0;
	int offset[12];
	
    pc.baud(115200);
    pc.format(8,Serial::None,1);
	L = 0; 
	for (int i=0; i<12; i++) {
		fscanf(fp,"%d", &offset[i]);
//		pc.printf("%d:%d/",i,offset[i]);
		if (i==0 || i==3 || i==5 ||
			i==6 || i==7 || i==8 || i==11)
			offset[i] = ang0 - offset[i];
		else	offset[i] = ang0 + offset[i];
	}
	fclose(fp);
	wait(1);
	L=1;
	wait(1);
	L=0;
	ServoControl s1(p15);
    ServoControl s2(p16);
    ServoControl s3(p17);
    ServoControl s4(p18);
    ServoControl s5(p19);
    ServoControl s6(p20);
    ServoControl s7(p26);
    ServoControl s8(p25);
    ServoControl s9(p24);
    ServoControl s10(p23);
    ServoControl s11(p22);
    ServoControl s12(p21);
	wait(1);
	/*
	s1.setPos(ang1-offset[0]);	//left foot role
	s2.setPos(ang1+offset[1]);	//left foot pitch
	s3.setPos(ang1+offset[2]);	//left knee pitch
	s4.setPos(ang1-offset[3]);	//left hip pitch
	s5.setPos(ang1+offset[4]);	//left hip role
	s6.setPos(ang1-offset[5]);	//left yaw
	
	s7.setPos(ang1-offset[6]);	//right foot role
	s8.setPos(ang1-offset[7]);	//right foot pitch
	s9.setPos(ang1-offset[8]);	//right knee pitch
	s10.setPos(ang1+offset[9]);	//right hip pitch
	s11.setPos(ang1+offset[10]);//right hip role
	s12.setPos(ang1-offset[11]);//right yaw
	wait(1);
	*/
	s1.setPos(offset[0]);	//left foot role
	s2.setPos(offset[1]+diff);	//left foot pitch
	s3.setPos(offset[2]-2*diff);	//left knee pitch
	s4.setPos(offset[3]-diff);	//left hip pitch
	s5.setPos(offset[4]);	//left hip role
	s6.setPos(offset[5]);	//left yaw
	
	s7.setPos(offset[6]);	//right foot role
	s8.setPos(offset[7]-diff);	//right foot pitch
	s9.setPos(offset[8]+2*diff);	//right knee pitch
	s10.setPos(offset[9]+diff);	//right hip pitch
	s11.setPos(offset[10]);//right hip role
	s12.setPos(offset[11]);//right yaw
	L=1;
	s1.setPower(1);
	s2.setPower(1);
	s3.setPower(1);
	s4.setPower(1);
	s5.setPower(1);
	s6.setPower(1);
	s7.setPower(1);
	s8.setPower(1);
	s9.setPower(1);
	s10.setPower(1);
	s11.setPower(1);
	s12.setPower(1);
	for (int i=0; i<diff; i+=10) {
	tarpos = diff - i;
	s1.setPos(offset[0]);	//left foot role
	s2.setPos(offset[1]+tarpos);	//left foot pitch
	s3.setPos(offset[2]-2*tarpos);	//left knee pitch
	s4.setPos(offset[3]-tarpos);	//left hip pitch
	s5.setPos(offset[4]);	//left hip role
	s6.setPos(offset[5]);	//left yaw
	
	s7.setPos(offset[6]);	//right foot role
	s8.setPos(offset[7]-tarpos);	//right foot pitch
	s9.setPos(offset[8]+2*tarpos);	//right knee pitch
	s10.setPos(offset[9]+tarpos);	//right hip pitch
	s11.setPos(offset[10]);//right hip role
	s12.setPos(offset[11]);//right yaw
	wait(0.1);
	}
	/*
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
	*/
    return 0;
}
