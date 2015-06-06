#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string.h>

class InvertKinematics
{
private:
	FILE *fp_M, *fp_P, *fp_A;
	unsigned int ServoNum;
	unsigned int LinkNum;
	float Link[84];
	std::vector<float> InitAngle;
	int setfp(char* fname_M, char* fname_P, char* fname_A);
	int closefp();
public:
	InvertKinematics();
	~InvertKinematics();
	int logMatrix(float*);
	int logPosition(float*);
	int logJointAngle(float*);

	int readLinkFile(char*);
	int readInitAngleFile(char*);
	int setLegTrajectory(char *, std::vector<float>&);

	int culMatrix(float*, float*);
	int setMatrixPara(unsigned int, unsigned int, float*, float*);
	int setMatrix(float, float*, float*);
	int getMotion(std::vector<float>& , unsigned int, float*);

};

InvertKinematics::InvertKinematics() {
	ServoNum = 12;
	LinkNum = 14;
	setfp("logMateix.txt","logPosition.txt", "walkAngle.txt");
}

InvertKinematics::~InvertKinematics() {
	closefp();
}

int InvertKinematics::setfp(char* fname_M, char* fname_P, char* fname_A) {
	fp_M = fopen(fname_M,"w");
	fp_P = fopen(fname_P,"w");
	fp_A = fopen(fname_A,"w");
	if(fp_M==NULL){
		std::cout<<fname_M<<" is not open.";
	 	return 1;
	}
	if(fp_P==NULL){
		std::cout<<fname_P<<" is not open.";
		return 1;
	}
	if(fp_A==NULL){
		std::cout<<fname_A<<" is not open.";
		return 1;
	}
	fclose(fp_M);
	fclose(fp_P);
	fclose(fp_A);
	fp_M = fopen(fname_M,"a");
	fp_P = fopen(fname_P,"a");
	fp_A = fopen(fname_A,"a");
	return 0;
}

int InvertKinematics::closefp() {
	if(fp_M==NULL){
		std::cout<<"Marix log is not close.";
		return 1;
	}
	if(fp_P==NULL){
		std::cout<<"Position log is not close.";
		return 1;
	}
	if(fp_A==NULL){
		std::cout<<"Angle is not open.";
		return 1;
	}
	fclose(fp_M);
	fclose(fp_P);
	fclose(fp_A);
	return 0;
}


int InvertKinematics::logMatrix(float angles[16]) {
	for (int i=0; i<4; i++) {
		fprintf(fp_M, "%.3f, %.3f, %.3f, %.3f \n",angles[0+i*4],angles[1+i*4],angles[2+i*4],angles[3+i*4]);
	}
	fprintf(fp_M,"\n");
	return 0;
}

int InvertKinematics::logPosition(float pos1[16]) {
	float ty = asin(-pos1[2]);
	float tx = asin(pos1[9]/cos(ty));
	float tz = 0;
	fprintf(fp_P, "%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",pos1[3], pos1[7], pos1[11], tx, ty, tz);
	return 0;
}

int InvertKinematics::logJointAngle(float ang[14]){
	for (int i=0; i<12; i++) fprintf(fp_A, "%.0f,",ang[i]);
	fprintf(fp_A, "\n");
	return 0;
}

int InvertKinematics::readLinkFile(char fname[]) {
	FILE *fp;
	std::cout<<"readLinkFile\n";
	fp = fopen(fname, "r");
	if(fp==NULL)	return 1;
	for (int i=0; i<LinkNum; i++) {
		fscanf(fp,  "%f, %f, %f, %f, %f, %f", &Link[0+i*6], &Link[1+i*6], &Link[2+i*6], &Link[3+i*6], &Link[4+i*6], &Link[5+i*6]);
	}
	fclose(fp);
	return 0;
}

int InvertKinematics::readInitAngleFile(char fname[]) {
	FILE *fp;
	float angle[12];
	std::cout<<"readInitAngleFile\n";
	fp = fopen(fname, "r");
	if(fp==NULL)	return 0;
	for (;;) {
		if (fscanf(fp, "%f,%f,%f,%f ,%f,%f,%f,%f ,%f,%f,%f,%f",
				&angle[0], &angle[1], &angle[2], &angle[3],
					&angle[4], &angle[5], &angle[6], &angle[7],
						&angle[8], &angle[9], &angle[10], &angle[11]) == EOF) break;
		for(int j=0; j<ServoNum; j++)	InitAngle.push_back(angle[j]);
	}
	fclose(fp);
	return InitAngle.size()/12;
}

int InvertKinematics::setLegTrajectory(char *fname ,std::vector<float> &traj){
	FILE *fp = fopen(fname,"r");
	float pos[8];
	if(fp==NULL)	return 1;
	while(1)
	{
		if(fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f", &pos[0], &pos[1], &pos[2], &pos[3], &pos[4], &pos[5], &pos[6], &pos[7]) == EOF)	break;
		for (int i=0; i<8; i++)		traj.push_back(pos[i]);
	}
	fclose(fp);
	return 0;
}


int InvertKinematics::culMatrix(float m1[16], float m2[16]){
	std::cout<<"culMatrix\n";
	float m3[16];
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			m3[j+i*4] = 0;
			for (int k=0; k<4; k++) {
				m3[j+i*4] += m1[k+i*4]* m2[j+k*4];
			}
		}
	}
	memcpy(m2, m3, 128);
	return 0;
}
		
int InvertKinematics::setMatrixPara(unsigned int no, unsigned int frame, float* angle, float link[6]) {
	if(no>LinkNum -1)	return 1;
	
	if(0<no && no<7)	*angle = InitAngle[no-1 + ServoNum*frame];
	else if(no>7)		*angle = InitAngle[no-2 + ServoNum*frame];
	else				*angle = 0;
	
	for(int i=0; i<6; i++)	link[i] = Link[i+no*6];
	return 0;
}
			
int InvertKinematics::setMatrix(float angle, float* link, float quat[16]) {
	float ang[3], pos[3];
	for(int i=0; i<3; i++)	ang[i] = M_PI*(*(link+i))*angle/180, pos[i] = *(link+i+3), 

	quat[0] = cos(ang[2])*cos(ang[1]);
	quat[1] = -sin(ang[2])*cos(ang[0]) + cos(ang[2])*sin(ang[1])*sin(ang[0]);
	quat[2] = sin(ang[2])*sin(ang[0]) + cos(ang[2])*sin(ang[1])*cos(ang[0]);
	quat[4] = sin(ang[2])*cos(ang[1]);
	quat[5] = cos(ang[2])*cos(ang[0]) + sin(ang[2])*sin(ang[1])*sin(ang[0]);
	quat[6] = -cos(ang[2])*sin(ang[0]) + sin(ang[2])*sin(ang[1])*cos(ang[0]);
	quat[8] = -sin(ang[1]);
	quat[9] = cos(ang[1])*sin(ang[0]);
	quat[10] = cos(ang[1])*cos(ang[0]);

	quat[3] = pos[0];
	quat[7] = pos[1];
	quat[11] = pos[2];

	quat[12] = 
	quat[13] =
	quat[14] = 0.0;
	quat[15] = 1.0;
	
	for(int i=0; i<16; i++)	std::cout<<quat[i]<<",";
	std::cout<<"\n";

	return 0;
}

int InvertKinematics::getMotion(std::vector<float> &tar, unsigned int frame, float angles[14]) {
	std::cout<<"getMotion\n";
	const int linknum2 = LinkNum/2;
	float link[14][6];
	float quat[14][16];
	double tarLength;
	float tarTheta[3];
	
	for (int i=0; i<LinkNum; i++) {
		setMatrixPara(i,frame,&angles[i],link[i]);
		setMatrix(angles[i],link[i], quat[i]);
	}
	
	//No.1, No.7 <=> contact point
	tar[1+8*frame] -= quat[0][7];	//y offset
	tar[5+8*frame] -= quat[7][7];
	tar[2+8*frame] -= quat[0][11];	//z offset
	tar[6+8*frame] -= quat[7][11];
	
	for (int i=0; i<2; i++) {
		std::cout<<"start: "<<i<<"\n";
		//Turn Y_joint and target
		tarTheta[2] = tar[3+i*4+8*frame];
		angles[6+i*linknum2] = tarTheta[2]*180/M_PI;
		tar[0+i*4+8*frame] = cos(-tarTheta[2])*(tar[0+i*4+8*frame]-link[6+i*linknum2][3]) - sin(-tarTheta[2])*(tar[1+i*4+8*frame]-link[6+i*linknum2][4]) + link[6+i*linknum2][3];
		tar[1+i*4+8*frame] = sin(-tarTheta[2])*(tar[0+i*4+8*frame]-link[6+i*linknum2][3]) + cos(-tarTheta[2])*(tar[1+i*4+8*frame]-link[6+i*linknum2][4]) + link[6+i*linknum2][4];
		printf("%.2f, %.2f\n", tar[0+i*4+8*frame], tar[1+i*4+8*frame]);		
				
		culMatrix(quat[6+i*linknum2 ], quat[5+i*linknum2 ]);
		//No.5 -> target	
		tarLength = (tar[0+i*4+8*frame]-quat[5+i*linknum2][3])*(tar[0+i*4+8*frame]-quat[5+i*linknum2][3])
			 	+ (tar[1+i*4+8*frame]-quat[5+i*linknum2][7])*(tar[1+i*4+8*frame]-quat[5+i*linknum2][7])
			  	+ (tar[2+i*4+8*frame]-quat[5+i*linknum2][11])*(tar[2+i*4+8*frame]-quat[5+i*linknum2][11]);
		tarLength = sqrt(tarLength);
		
		//x-z plane
		if(tar[0+i*4+6*frame]-quat[5+i*linknum2][3] != 0.0)	
				tarTheta[1] = -M_PI/2 -atan2(tar[2+i*4+8*frame]-quat[5+i*linknum2][11], tar[0+i*4+8*frame]-quat[5+i*linknum2][3]);
		else	tarTheta[1] = 0;
		
		std::cout<<"/"<<tarLength<<","<<tarTheta[1]<<"\n";

		angles[3+i*linknum2] = -2*acos((float)tarLength/(fabs(link[2+i*linknum2][5] + link[3+i*linknum2][5])))*180/M_PI;
		angles[2+i*linknum2] = -tarTheta[1]*180/M_PI - angles[3+i*linknum2]/2;
		angles[4+i*linknum2] = tarTheta[1]*180/M_PI - angles[3+i*linknum2]/2;
		
		//y-z plane
		if(tar[1+i*4+6*frame]-quat[5+i*linknum2][7] != 0.0)
				tarTheta[0] = M_PI/2 + atan2(tar[2+i*4+8*frame]-quat[5+i*linknum2][11], tar[1+i*4+8*frame]-quat[5+i*linknum2][7]);
		else	tarTheta[0] = 0.0;
		angles[5+i*linknum2] = tarTheta[0]*180/M_PI;
		angles[1+i*linknum2] = -angles[5+i*linknum2];
				
		for (int j=0; j<LinkNum; j++) 		setMatrix(angles[j],link[j],quat[j]);
		for (int j=linknum2-1; j>0; j--) 	culMatrix(quat[j+i*linknum2], quat[j-1+i*linknum2]);
	
		logMatrix(quat[0+i*linknum2]);
		logPosition(quat[0+i*linknum2]);
	}
	
	for(int i=0; i<LinkNum; i++){
		if(i<6)			angles[i] = angles[i+1];
		else if(i<12)	angles[i] = angles[i+2];
		else			angles[i] = 0;
	}
	return 0;
}
