#include "culTrajectory.h"

int main() {
	FILE *fp = fopen("log.txt","w");
	culTrajectory cultra;
	int stepx = 20;
	int stepy = 10;
	double posx = 0.0;
	double posy = 0.0;
	double velx = 0.0;
	double vely = 0.0;
	double lx = -5.0;
	double ly = -5.0;

	double posx1, posy1, velx1, vely1;
	
	for (int i=0; i<300; i++) {
		fprintf(fp,"%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx, posy, lx, ly, velx, vely);
		cultra.cul_motion(stepx, stepy, posx, posy, velx, vely, lx, ly,
			&posx1, &posy1, &velx1, &vely1);
		cultra.cul_Lpoint(i, stepx, stepy, posx1, posy1, velx1, vely1, lx, ly,	&lx, &ly);
		posx = posx1;
		posy = posy1;
		velx = velx1;
		vely = vely1;
		printf("%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx1, posy1, lx, ly, velx1, vely1);
		fprintf(fp,"%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx1, posy1, lx, ly, velx1, vely1);
	}
	fclose(fp);
	return 0;
}

