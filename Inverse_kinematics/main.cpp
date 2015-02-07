#include "InvertKinematics.h"

int main(){
	std::vector<float> target;	//foot trajectory: [lx,ly,lz,rx,ry,rz] x n(step)
	float angle[14];			//joint angles: 
	InvertKinematics kine;

	if(kine.readLinkFile("linkPara.txt"))	return 1;
	int frame = kine.readInitAngleFile("initAngles.txt");
	if(!frame)	return 1;
	if(kine.setLegTrajectory("trajectory.txt", target))	return 1;
	
	for(int i=0; i<target.size()/6; i++) {
		kine.getMotion(target, i, angle);
		kine.logJointAngle(angle);
	}
	return 0;
}
	
