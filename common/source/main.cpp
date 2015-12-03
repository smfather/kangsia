#include <iostream>
#include <crtdbg.h>
#include "parSIM.h"
#include "CouplingSystem.h"

// #ifndef _DEBUG
// #define new new(_CLIENT_BLOCK,__FILE__, __LINE)
// #endif
vector3<double> MovingCondition(vector3<double> op, double t)
{
	op.x = 7.0 - 1.5*t;
	op.z = 1.5 + 1.5 * sin(0.2 * PI*t);// * vector3<double>(1.0, 0.0, 0.0);
	return op;
}

using namespace parSIM;

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Log::SetLevel(Log::Info);
	Log::SetOutput("console_log.txt");

	Simulation::dimension = DIM_3;
	Simulation::sim_time = 10.0;
	Simulation::save_step = 500;
	Simulation::gravity = vector3<double>(0.0, -9.80665, 0.0);
	//Simulation::caseName = "trawl_moving_simulation_angle20_type1";
	Simulation::caseName = "trawl_contact_test";
	//Simulation::caseName = "trawl_moving_simulation_angle30_type2_real";
	//Simulation::caseName = "cohesion_test";
	Simulation::base_path = "C:/C++/";
	//Simulation::specific_data = "C:/C++/result/trawl_moving_simulation_angle10_type2_start_version2_144.dat";
	//Simulation::specific_data = "C:/C++/result/trawl_moving_simulation_angle30_type2_stable_particle_condition.dat";
	//Simulation::specific_data = "C:/C++/result/rect2.dat";

	force::cohesive = 0.0;

	particles::radius = 0.0025;

	Demsimulation *dem = new Demsimulation("simDem");
	dem->setIntegration(VELOCITY_VERLET);
	dem->setDevice(GPU);
	
	Mbdsimulation *mbd = new Mbdsimulation("simMbd");
	mbd->setIntegration(IMPLICIT_HHT);
	mbd->setDevice(CPU);

	geo::cube *cube_particle = new geo::cube(dem, "particle geometry");
	cube_particle->define(vector3<double>(2.0, 0.07, 0.6), vector3<double>(0.0, 0.0, 0.0), MEDIUM_CLAY, PARTICLE);
	//cube_particle->define(vector3<double>(0.0, 0.0, 0.0), vector3<double>(0.0, 0.0, 0.0), MEDIUM_CLAY, PARTICLE);

	geo::cube *cube_boundary = new geo::cube(dem, "boundary geometry");
	cube_boundary->define(vector3<double>(2.0, 0.5, 0.6), vector3<double>(0.0, 0.0, 0.0), ACRYLIC, BOUNDARY);

// 	geo::shape *shape_trawl = new geo::shape(mbd, "trawl");
// 	shape_trawl->define("C:/C++/case/dem/B1N_ap203_30_non-scale.dat", vector3<double>(0.2, 0.09, 0.3), STEEL, MASS);

	mass::rigid_body *ground = new mass::rigid_body(mbd, "ground");
	ground->define(0, 0.0, vector3<double>(0.0, 0.0, 0.0), vector3<double>(0.0, 0.0, 0.0), vector3<double>(0.0, 0.0, 0.0), euler_parameter<double>(1.0, 0.0, 0.0, 0.0));

// 	mass::rigid_body *rb_trawl = new mass::rigid_body(mbd, "trawl", shape_trawl);
// 	rb_trawl->define(1, 200, vector3<double>(5.556e-4, 0.001, 0.002), vector3<double>(3.81e-5, -5.421e-20, 0), vector3<double>(2.0, 0.9, 1.0), euler_parameter<double>( 0.984807753012208, 0.0,   -0.173648177666930, 0.0));
	//rb_trawl->define(1, 200, vector3<double>(5.556e-4, 0.001, 0.002), vector3<double>(3.81e-5, -5.421e-20, 0), vector3<double>(17.0, 1.1, 2.5), euler_parameter<double>( 0.984807753012208, 0.0,   -0.087155742747658, 0.0));
	//rb_trawl->define(1, 200, vector3<double>(5.556e-4, 0.001, 0.002), vector3<double>(3.81e-5, -5.421e-20, 0), vector3<double>(17.0, 0.9, 2.5), euler_parameter<double>( 1.0, 0.0, 0.0, 0.0));
 	//rb_trawl->setMovingFunction(MovingCondition);

	if(!dem->initialize()){
		std::cout << "ERROR : The initialize of dem simulation is failed." << std::endl;
		return 0;
	}

	if(!mbd->initialize())
	{
		std::cout << "ERROR : The initialize of mbd simulation is failed." << std::endl;
		return 0;
	}

	CouplingSystem *csys = new CouplingSystem(dem, mbd);
	if(!csys->Run()){
		std::cout << "ERROR : The simulation is failed. Check for your system." << std::endl;
		return 0;
	}
	delete csys;
	return 0;
}

