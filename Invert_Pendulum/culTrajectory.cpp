#include "culTrajectory.h"

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

int culTrajectory::cul_LIP_Physics(double posx0, double posy0,
		double velx0, double vely0, double lx, double ly,  
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

int culTrajectory::cul_Physics(double posx0, double posy0, 
		double velx0, double vely0, double lx, double ly,  
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

int culTrajectory::cul_Lpoint(int num, double vx, double vy,
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

