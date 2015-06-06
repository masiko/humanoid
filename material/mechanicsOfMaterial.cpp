#include "stdio.h"

float culInertiaOfArea_L(float H, float B, float t) {
	printf("culInertiaOfArea_L\n");
	float b = B-t;
	float e1 = (t*H*H + b*t*t)/(t*H + b*t)/2;
	float e2 = H - e1;
	float h = e1 - t;

	float I = (B*e1*e1*e1 - b*h*h*h + t*e2*e2*e2)/2;

	return I;
}

int main(){
	FILE *fp = fopen("dst.txt","w");
	float H=0, B=0, t=0;
	float I, z;
	char c[10];
	
	while(1){
		printf("H: ");
		scanf("%f", &H);
		if(H>0)	break;
	}

	while(1){
		printf("B: ");
		scanf("%f", &B);
		if(B>0)	break;
	}

	while(1){
		printf("t: ");
		scanf("%f", &t);
		if(t>0)	break;
	}

	I = culInertiaOfArea_L(H,B,t);
	z = 2*I/H;

	printf("I: %f\nz: %f\n", I, z);
	fprintf(fp, "H:%f\nB:%f\nt:%f\n", H,B,t);
	fprintf(fp, "I:%f\nz:%f\n", I, z);

	fclose(fp);
	
	gets(c);
	return 0;
}

