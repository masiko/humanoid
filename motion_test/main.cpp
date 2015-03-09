#include "Servo_Control.h"
#include <stdio.h>
#include <vector>

#define DOF (12)

DigitalOut L(LED1);
LocalFileSystem local("local");

int setInitPos(int offset[], int dor[]) {
	// read offset angles of init position
	FILE *fp = fopen("/local/offset_a.txt","r");
	if (fp==NULL)	return 1;
	for (int i=0; i<DOF; i++) {
		fscanf(fp,"%d", &offset[i]);
	}
	fclose(fp);
	// read direction of rotation for + rotate
	fp = fopen("/local/dor.txt","r");
	if (fp==NULL)	return 1;
	for (int i=0; i<DOF; i++) {
		fscanf(fp,"%d", &dor[i]);
	}
	fclose(fp);
	// set init position
	for(int i=0; i<DOF; i++) {
		offset[i] = 1500 + dor[i]*offset[i];
	}
	return 0;
}

int readMotion(char* fname, std::vector<int>* v) {
	int i=0;
	int dt;			//ms
	int ang[DOF];	//deg
	//read motion file
	FILE *fp = fopen(fname,"r");
	if (fp==NULL)	return 1;

	while(i<30) {
		if (fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&ang[0],&ang[1],&ang[2],&ang[3],
		&ang[4],&ang[5],&ang[6],&ang[7],
		&ang[8],&ang[9],&ang[10],&ang[11],
		&dt)==EOF)	break;
		
		for (int j=0; j<DOF; j++)	v->push_back(ang[j]*10);
		v->push_back(dt);
		i++;
	}
	fclose(fp);
	return 0;
}


int main() {
	int offset[DOF];
	int dor[DOF];
	if (setInitPos(offset, dor))	return 1;
	std::vector<ServoControl> s;
	
	s.push_back(ServoControl(p15));	//left foot role
	s.push_back(ServoControl(p16));
	s.push_back(ServoControl(p17));
	s.push_back(ServoControl(p18));
	s.push_back(ServoControl(p19));
	s.push_back(ServoControl(p20));
	
	s.push_back(ServoControl(p26));	//right foot role
	s.push_back(ServoControl(p25));
	s.push_back(ServoControl(p24));
	s.push_back(ServoControl(p23));
	s.push_back(ServoControl(p22));
	s.push_back(ServoControl(p21));
	
	for (int i=0; i<DOF; i++)	s[i].setPos(offset[i]);
	for (int i=0; i<DOF; i++)	s[i].setPower(1);

	std::vector<int> motionframe;
	char fname[] = "/local/motion.txt";
	if (readMotion(fname, &motionframe))	return 1;
	int fnum = motionframe.size()/13;

	for (int i=0; i<fnum; i++) {
		L=1;
		for (int j=0; j<DOF; j++) {
			s[j].setPos(offset[j] + dor[j]*motionframe[13*i+j]);
		}
		wait_ms(motionframe[12]);
		L=0;
		wait(0.5);
	}

	for (int i=0; i<DOF; i++)	s[i].setPower(0);
	return 0;
}

