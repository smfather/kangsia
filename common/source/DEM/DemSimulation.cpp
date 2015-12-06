#include "DEM/DemSimulation.h"
#include "view_particles.h"
#include "cu_dem_dec.cuh"
#include <QtWidgets>

#include <cuda_runtime.h>
#include <vector_types.h>

#include <helper_functions.h>
#include <helper_cuda.h>

DemSimulation::DemSimulation()
{
	pos = vel = omega = force = moment = NULL;
	d_pos = d_vel = d_omega = d_force = d_moment = NULL;
}

DemSimulation::~DemSimulation()
{
	if (pos) delete[] pos; pos = NULL;
	if (vel) delete[] vel; vel = NULL;
	if (omega) delete[] omega; omega = NULL;
	if (force) delete[] force; force = NULL;
	if (moment) delete[] moment; moment = NULL;
	if (d_pos) cudaFree(d_pos); d_pos = NULL;
	if (d_vel) cudaFree(d_vel); d_vel = NULL;
	if (d_omega) cudaFree(d_omega); d_omega = NULL;
	if (d_force) cudaFree(d_force); d_force = NULL;
	if (d_moment) cudaFree(d_moment); d_moment = NULL;
}

bool DemSimulation::Initialize(std::map<QString, parview::Object*>& objs)
{
	unsigned int np = 0;
	float maxRadius = 0.0f;
	gridSize[0] = 128; gridSize[1] = 128; gridSize[2] = 128;
	worldOrigin[0] = 0.0f; worldOrigin[1] = 0.0f; worldOrigin[2] = 0.0f;
	viewPars = dynamic_cast<parview::particles*>(objs.find("particles")->second);
	np = viewPars->Np();
	pos = new float[np * 4];
	vel = new float[np * 4];
	omega = new float[np * 4];
	force = new float[np * 4];
	moment = new float[np * 4];
	memcpy(pos, viewPars->getPosition(0), sizeof(float)*np * 4);
	memset(vel, 0, sizeof(float)*np * 4);
	memset(omega, 0, sizeof(float)*np * 4);
	memset(force, 0, sizeof(float)*np * 4);
	memset(moment, 0, sizeof(float)*np * 4);
	for (unsigned int i = 0; i < np; i++){
		force[i * 4 + 3] = viewPars->Material().density * 4.0f * PI * pow(pos[i * 4 + 3], 3) / 3.0f;
		moment[i * 4 + 3] = 2.0f * force[i * 4 + 3] * pow(pos[i * 4 + 3], 2) / 5.0f;
		if (maxRadius < pos[i * 4 + 3]){
			maxRadius = pos[i * 4 + 3];
		}
	}

	// CUDA Memory allocation
	checkCudaErrors(cudaMalloc((void**)&d_pos, sizeof(float)*np * 4));
	checkCudaErrors(cudaMalloc((void**)&d_vel, sizeof(float)*np * 4));
	checkCudaErrors(cudaMalloc((void**)&d_omega, sizeof(float)*np * 4));
	checkCudaErrors(cudaMalloc((void**)&d_force, sizeof(float)*np * 4));
	checkCudaErrors(cudaMalloc((void**)&d_moment, sizeof(float)*np * 4));

	// Copy the memory from host to device
	checkCudaErrors(cudaMemcpy(d_pos, pos, sizeof(float)*np * 4, cudaMemcpyHostToDevice));
	checkCudaErrors(cudaMemcpy(d_vel, vel, sizeof(float)*np * 4, cudaMemcpyHostToDevice));
	checkCudaErrors(cudaMemcpy(d_omega, omega, sizeof(float)*np * 4, cudaMemcpyHostToDevice));
	checkCudaErrors(cudaMemcpy(d_force, force, sizeof(float)*np * 4, cudaMemcpyHostToDevice));
	checkCudaErrors(cudaMemcpy(d_moment, moment, sizeof(float)*np * 4, cudaMemcpyHostToDevice));

// 	device_parameters paras;
// 	paras.np = np;
// 	paras.nsp = 0;// cdetect.getNumShapeVertex();
// 	paras.dt = BaseSimulation::dt;
// 	paras.half2dt = 0.5*paras.dt*paras.dt;
// 	paras.gravity = make_float3(BaseSimulation::gravity[0], BaseSimulation::gravity[1], BaseSimulation::gravity[2]);
// 	paras.cell_size = maxRadius * 2.0f;
// 	paras.ncell = gridSize[0] * gridSize[1] * gridSize[2];
// 	paras.grid_size = make_uint3(gridSize[0], gridSize[1], gridSize[2]);
// 	paras.world_origin = make_float3(worldOrigin[0], worldOrigin[1], worldOrigin[2]);
// 	//contact_coefficient ppc = cforce.getCoefficient("particle");
// // 	paras.kn = ppc.kn;
// // 	paras.vn = ppc.vn;
// // 	paras.ks = ppc.ks;
// // 	paras.vs = ppc.vs;
// // 	paras.mu = ppc.mu;
// // 	paras.cohesive = force::cohesive;
// 	setSymbolicParameter(&paras);
// 	//Dem->cu_integrator_binding_data(Dem->getParticles()->cu_Position(), Dem->getParticles()->cu_Velocity(), Dem->getParticles()->cu_Acceleration(), Dem->getParticles()->cu_AngularVelocity(), Dem->getParticles()->cu_AngularAcceleration(), cforce.cu_Force(), cforce.cu_Moment());
// // 	for (std::map<Q, geometry*>::iterator Geo = Dem->getGeometries()->begin(); Geo != Dem->getGeometries()->end(); Geo++){
// // 		if (Geo->second->GeometryUse() != BOUNDARY) continue;
// // 		Geo->second->define_device_info();
// // 	}
	return true;
}

void DemSimulation::CpuRun()
{

}

void DemSimulation::GpuRun()
{

}