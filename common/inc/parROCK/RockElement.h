#ifndef ROCKELEMENT_H
#define ROCKELEMENT_H

#include <string>


class RockElement
{
public:
	RockElement();
	~RockElement();

	static double maxDiameter;
	static double diameterRatio;
	static double porosity;			// ���ط�
	static double density;
	static double ryoungsModulus;
	static double rstiffnessRatio;
	static double friction;
};


#endif