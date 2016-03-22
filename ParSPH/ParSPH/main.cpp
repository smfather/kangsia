#include "parSPH.h"

using namespace parsph;

int main(int argc, char** argv)
{
	std::string name = "isph_wave_generation_with_floating";
	t_solver solver = ISPH;

	incompressible_sph *isph = new incompressible_sph(name);
	writer *write = new writer(isph, "C:/C++/sph_result/");	

	// set simulation option
	isph->setDevice(GPU);
	isph->setDimension(DIM2);
	isph->setTimeStep(0.25e-3);
	isph->setExportTimeStep(0.1);
	isph->setProjectionForm(NonIncremental, 1);
	//isph->setCorrection(GRADIENT_CORRECTION);
	isph->setPPESolver(250, 1e-2);
	isph->setParticleSpacing(0.002);
	isph->setKernel(CUBIC_SPLINE, false, 0.0028);
	isph->setGravity(0.0, -9.80665, 0.0);
	//isph->setSolverTolerance(5);
	isph->setParticleShifting(false, 1, 0.01);

	// set writer
	write->setExportVariable(POSITION);
	write->setExportVariable(PRESSURE);
	write->setExportVariable(VELOCITY);
	write->setExportDataType(BINARY);

	if(!write->initialize()){
		std::cout << "Error : Writer is not initialized." << std::endl;
		return 0;
	}

	// set fluid
	isph->setDensity(1000.0);
	isph->setViscosity(1e-3);
	isph->setBucketFillLocation(vector3<double>(-0.378, 0.078, 0.0));

	// set boundary
	vector3<double> boundMin = vector3<double>(-0.5, -0.1, 0.0);
	vector3<double> boundMax = vector3<double>(0.7, 0.5, 0.0);

	isph->setBoundary(boundMin, boundMax);

	// set scene
	geo::Line *fluid_top = new geo::Line(isph, FLUID, "fluid top");
	fluid_top->Define(vector2<double>(-0.38, 0.08), vector2<double>(0.0, 0.08), true);

	geo::Line *fluid_right = new geo::Line(isph, FLUID, "fluid right");
	fluid_right->Define(vector2<double>(0.0, 0.08), vector2<double>(0.0, 0), true);

	geo::Line *bottom_wall = new geo::Line(isph, BOUNDARY, "bottom_wall");
	bottom_wall->Define(vector2<double>(-0.38, 0), vector2<double>(0.0, 0), true, true);

	geo::Line *left_wall = new geo::Line(isph, BOUNDARY, "left wall");
	left_wall->Define(vector2<double>(-0.38, 0.1499), vector2<double>(-0.38, 0), true);

	left_wall->SetExpressionMovement(false);
	left_wall->SetMovementExpression(0.5, 0.6, vector3<double>(0.1, 0.0, 0.0));

	geo::Line *right_wall = new geo::Line(isph, BOUNDARY, "right wall");
	right_wall->Define(vector2<double>(0.0, 0), vector2<double>(0.0, 0.1499), true);

	// floating
// 	geo::Square *body = new geo::Square(isph, BOUNDARY, "floating body");
// 	body->Define(vector3<double>(-0.19, 0.15, 0.0), vector3<double>(0.02, 0.02, 0.0), true);
// 	body->DefineMass(0.5, vector3<double>(1.0, 1.0, 1.0), vector3<double>(-0.19, 0.15, 0.0), vector4<double>(1.0, 0.0, 0.0, 0.0));
// 	geo::Line *uwall = new geo::Line(isph, BOUNDARY, "uwall");
// 	uwall->Define(vector2<double>(-0.20, 0.160), vector2<double>(-0.18, 0.160), true);
// 
// 	geo::Line *lwall = new geo::Line(isph, BOUNDARY, "lwall");
// 	lwall->Define(vector2<double>(-0.20, 0.140), vector2<double>(-0.20, 0.160), true);
// 
// 	geo::Line *bwall = new geo::Line(isph, BOUNDARY, "bwall");
// 	bwall->Define(vector2<double>(-0.18, 0.140), vector2<double>(-0.20, 0.140), true);
// 
// 	geo::Line *rwall = new geo::Line(isph, BOUNDARY, "rwall");
// 	rwall->Define(vector2<double>(-0.18, 0.160), vector2<double>(-0.18, 0.140), true);

	if(!isph->initialize())
	{
		std::cout << "Error : Setting up sph initialize failed." << std::endl;
		return 0;
	}
	write->exportBoundaryData();
	write->exportVariableData(CPU);

	double endTime = 1.0;
	double durationTime = 0;
	double partTime = 0;
	while(endTime > durationTime){
		std::cout << "time : " << durationTime << std::endl;
		isph->runModelExpression(isph->TimeStep(), durationTime);
		double new_dt = isph->Device() == CPU ? isph->run() : isph->gpu_run();
		durationTime += new_dt;
		partTime += new_dt;
		if(partTime > 0.001){
			write->exportVariableData(isph->Device());
			partTime = 0.0;
		}
	}

	return 0;

}