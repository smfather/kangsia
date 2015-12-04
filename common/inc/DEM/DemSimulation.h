#ifndef DEMSIMULATION_H
#define DEMSIMULATION_H

#include "BaseSimulation.hpp"
#include <map>
//#include "view_particles.h"

class DemSimulation : public BaseSimulation<float>
{
	Q_OBJECT

public:
	DemSimulation();
	~DemSimulation();

	bool Initialize(std::map<QString, parview::Object*>& objs);
	
	virtual void CpuRun();
	virtual void GpuRun();

private:
	// particle variables
	float *pos;
	float *vel;
	float *omega;
	float *force;
	float *moment;

	float* d_pos;
	float* d_vel;
	float* d_omega;
	float* d_force;
	float* d_moment;

	parview::particles* viewPars;
};

#endif