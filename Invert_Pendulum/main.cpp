#include "culTrajectory.h"

int main() {
	FILE *fp = fopen("log.txt","w");
	culTrajectory cultra;
	int stepx = 20;
	int stepy = 30;
	double posx = 0.0;
	double posy = 0.0;
	double velx = 0.0;
	double vely = 0.0;
	double lx = -5.0;
	double ly = -20;

	double posx1, posy1, velx1, vely1;
	
//	cultra.set_cycl(0.8);
//	cultra.set_cogz(800);
	
	for (int i=0; i<300; i++) {
		fprintf(fp,"n:%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx, posy, lx, ly, velx, vely);
		cultra.cul_motion(stepx, stepy, posx, posy, velx, vely, lx, ly,
			&posx1, &posy1, &velx1, &vely1);
		cultra.cul_Lpoint_fb(i, 100, 30, posx1, posy1, velx1, vely1, lx, ly,	&lx, &ly);
		posx = posx1;
		posy = posy1;
		velx = velx1;
		vely = vely1;
		printf("f:%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx1, posy1, lx, ly, velx1, vely1);
		fprintf(fp,"f:%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx1, posy1, lx, ly, velx1, vely1);
	}
	fclose(fp);
	return 0;
}

