#include "culTrajectory.h"

int main() {
	FILE *ip = fopen("walk-plan.txt","r");
	FILE *lp = fopen("log.txt","w");
	FILE *tp = fopen("trajectory.txt","w");
	culTrajectory cultra;
	int stepx = 20;
	int stepy = 30;
	double walk_cycl = 0.2;
	double posx = 0.0;
	double posy = 0.0;
	double posz = 0.0;
	double velx = 0.0;
	double vely = 0.0;
	double lx =  0.0;
	double ly =  0.0;
	double ther = 0.0;
	double thel = 0.0;

	double posx1, posy1, velx1, vely1, lx1, ly1;
	double tvx=0.0;
	double tvy=0.0;
	
	if (fscanf(ip, "%lf,%lf,%lf,%lf",&posz,&walk_cycl,&lx,&ly)==EOF) {
		fclose(ip);
		fclose(lp);
		fclose(tp);
		return 0;
	}

	cultra.set_cycl(walk_cycl);
	cultra.set_cogz(posz);
	
	for (int i=0; i<500; i++) {

		if (fscanf(ip, "%lf,%lf",&tvx,&tvy)==EOF)	break;
		fprintf(lp,"n:%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx, posy, lx, ly, velx, vely);

		cultra.cul_Physics(posx, posy, velx, vely, lx, ly, &posx1, &posy1, &velx1, &vely1);
		cultra.cul_Lpoint(i, tvx, tvy, posx1, posy1, velx1, vely1, lx, ly,	&lx1, &ly1);
		printf("f:%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx1, posy1, lx, ly, velx1, vely1);

		fprintf(lp,"f:%.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf\n", posx1, posy1, lx1, ly1, velx1, vely1);
		if (i%2) {//+ left leg
			fprintf(tp,"%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f\n",lx-posx1,ly-posy,-posz,ther,lx1-posx1,ly1-posy1,-posz,thel);
		} else {//- right leg
			fprintf(tp,"%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f,%.0f\n",lx1-posx1,ly1-posy1,-posz,ther,lx-posx1,ly-posy1,-posz,thel);
		}
		posx = posx1;
		posy = posy1;
		velx = velx1;
		vely = vely1;
		lx = lx1;
		ly = ly1;
	}
	fclose(ip);
	fclose(lp);
	fclose(tp);
	return 0;
}

