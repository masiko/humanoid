#include <iostream>
#include <stdio.h>
#include <math.h>

class culTrajectory
{
private:
	const double G;		//[mm/s^2]
	double walk_cycle;	//[sec]
	double cog_z;		//[mm]
	double Tc;			//[1/s]int stepx, int stepy, 
public:
	culTrajectory();
	~culTrajectory();
	int set_cycl(double f);
	int set_cogz(double z);
	int cul_LIP_motion(int stepx, int stepy, 
		double posx0, double posy0, double velx0, double vely0, double lx, double ly,  
		double* posx, double* posy, double* velx, double* vely);
	int cul_motion(int stepx, int stepy, 
		double posx0, double posy0, double velx0, double vely0, double lx, double ly,  
		double* posx, double* posy, double* velx, double* vely);
	int cul_Lpoint(int num, int stepx, int stepy,
		double posx0, double posy0, double velx0, double vely0,
		double lx0, double ly0, double* lx, double* ly);
	int cul_Lpoint_fb(int num, double vx, double vy,
		double posx0, double posy0, double velx0, double vely0,
		double lx0, double ly0, double* lx, double* ly);
};





culTrajectory::culTrajectory(): G(9807),  walk_cycle(0.2), cog_z(180) {
	Tc = sqrt(cog_z/G);
}

culTrajectory::~culTrajectory(){}

int culTrajectory::set_cycl(double c) {
	walk_cycle = c;
	return 0;
}
	
int culTrajectory::set_cogz(double z) {
	cog_z = z;
	Tc = sqrt(cog_z/G);
	return 0;
}

int culTrajectory::cul_LIP_motion(int stepx, int stepy, 
		double posx0, double posy0, double velx0, double vely0, double lx, double ly,  
		double* posx, double* posy, double* velx, double* vely) {
	static double global_T = 0.0;
	double freq = (global_T+walk_cycle)/Tc;
	double C,S;
	printf("culTrajectory::cul_motion\n");
	C = cosh(freq);
	S = sinh(freq);
	*posx = (posx0-lx)*C + Tc*velx0*S + lx;
	*velx = (posx0-lx)*S/Tc + velx0*C;

	*posy = (posy0-ly)*C + Tc*vely0*S + ly;
	*vely = (posy0-ly)*S/Tc + vely0*C;

	global_T += walk_cycle;
	return 0;
}

int culTrajectory::cul_motion(int stepx, int stepy, 
		double posx0, double posy0, double velx0, double vely0, double lx, double ly,  
		double* posx, double* posy, double* velx, double* vely) {
	double freq = walk_cycle/Tc;
	double C,S;
	printf("culTrajectory::cul_motion\n");
	C = cosh(freq);
	S = sinh(freq);
	*posx = (posx0-lx)*C + Tc*velx0*S + lx;
	*velx = (posx0-lx)*S/Tc + velx0*C;

	*posy = (posy0-ly)*C + Tc*vely0*S + ly;
	*vely = (posy0-ly)*S/Tc + vely0*C;

	return 0;
}

int culTrajectory::cul_Lpoint(int num, int stepx, int stepy,
		double posx0, double posy0, double velx0, double vely0,
		double lx0, double ly0, double* lx, double* ly) {
	const int a = 10;
	const int b = 1;
	double C,S,D;
	double freq = walk_cycle/Tc;
	C = cosh(freq);
	S = sinh(freq);
	num = num%2 ? 1 : -1;
	double lx1 = lx0 + stepx;
	double ly1 = ly0 - (num)*stepy;
	double ex = (posx0-lx1)*C + Tc*velx0*S + lx1;
	double ey = (posx0-ly1)*C + Tc*vely0*S + ly1;
	double evx = (ex-lx1)*S/Tc + velx0*C;
	double evy = (ey-ly1)*S/Tc + vely0*C;
	
	printf("culTrajectory::cul_Lpoint\n");
	D = a*(C-1.0)*(C-1.0) + b*(S/Tc)*(S/Tc);

	*lx = -a*(C-1.0)*(ex-C*posx0-Tc*S*velx0)/D - b*S*(evx-posx0*S/Tc-C*velx0)/(Tc*D);
	*ly = -a*(C-1.0)*(ey-C*posy0-Tc*S*vely0)/D - b*S*(evy-posy0*S/Tc-C*vely0)/(Tc*D);

	return 0;
}

int culTrajectory::cul_Lpoint_fb(int num, double vx, double vy,
		double posx0, double posy0, double velx0, double vely0,
		double lx0, double ly0, double* lx, double* ly) {
	double C,S;
	double freq = walk_cycle/Tc;
	C = cosh(freq);
	S = sinh(freq);
	num = num%2 ? 1 : -1;
	
	printf("culTrajectory::cul_Lpoint_fb\n");

	*lx = posx0 + Tc*(C)*velx0/(S) - Tc/(S)*vx;
	*ly = posy0 + Tc*(C)*vely0/(S) - Tc/(S)*vy*num;

	return 0;
}
