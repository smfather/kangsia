#include "RockSimulation.h"

typedef vector3<double> vec3;
typedef vector2<double> vec2;

vector3<double> func1(double t)
{
	return t*vector3<double>(20.0, 0.0, 0.0) + vector3<double>(0.0, -0.001, 0.0);
}

int main(int argc, char** argv)
{
	Simulation *sim = new RockSimulation("C:/C++/result/", "pickandrock3");
	//sim->SpecificData() = "C:/C++/result/pickandrock1_nonfloating.dat";

	sim->WorldOrigin() = vector3<double>(0.0, 0.0, 0.0);;
	sim->GridSize() = vector3<unsigned int>(128, 128, 128);
	sim->Device() = CPU;
	sim->Dimension() = DIM_2;

	RSP::tm_req_isostr_tol = 0.5;
	RSP::tm_req_isostr = -1.0e6;
	RSP::flt_def = 6;
	RSP::flt_r_mult = 1.00005;
	RSP::f_tol = 0.1;
	RSP::relax = 1.5;
	RSP::hyst = 0.9;

	WallElement::wYoungsFactor = 1.1;
	WallElement::wfriction = 0.5;

	RockElement::maxDiameter = 0.0008;
	RockElement::diameterRatio = 1.0;
	RockElement::porosity = 0.16;
	RockElement::density = 2630;
	RockElement::ryoungsModulus = 62e+9;
	RockElement::rstiffnessRatio = 2.5;
	RockElement::friction = 0.5;

	CementElement::brmul = 1;
	CementElement::cyoungsModulus = 62e+9;
	CementElement::cstiffnessRatio = 2.5;
	CementElement::maxTensileStress = 157e+6;
	CementElement::maxShearStress = 175e+6;
	CementElement::tensileStdDeviation = 36e+6;
	CementElement::shearStdDeviation = 40e+6;

	utility::writer::fileFormat = 'b';
	utility::writer::solverType = 'd';
	utility::writer::SetSimulation(sim);

	geo::Cube *specimen = new geo::Cube(sim, "specimen", GEO_PARTICLE);
	//specimen->Define(vec2(0.0, 0.0), vec2(0.08, 0.04));
	specimen->Define(vector3<double>(0.0, -0.04, -0.04), vector3<double>(0.12, 0.0, 0.04));
	//specimen->Define(vector3<double>(0.0, -0.0096, -0.01), vector3<double>(0.02, 0.0, 0.01));
	//specimen->Define(vec2(0.0, 0.0), vec2(0.0032, 0.0032));

//	Object* pick = new Object(sim);
///*	pick->CenterOfGravity(vector3<double>(-0.001, 0.016, 0.0));
//	pick->addLine(vector3<double>(-0.034197056444066, 0.034476860207004, 0.0), vector3<double>(-0.001, 0.016, 0.0), vector3<double>(0.729537204140085, 0.683941128881330, 0.0));
//	pick->addLine(vector3<double>(-0.001, 0.016, 0.0), vector3<double>(-0.046423834544263, 0.016569533817705, 0.0), vector3<double>(-0.371390676354105, -0.928476690885259, 0.0));*/
//	pick->CenterOfGravity(vector3<double>(0.000156431677, 0.016, 0.0));
//	pick->addLine(vector3<double>(-0.033040624, 0.034476860207004, 0.0), vector3<double>(0.000156431677, 0.016, 0.0), vector3<double>(0.729537204140085, 0.683941128881330, 0.0));
//	pick->addLine(vector3<double>(0.000156431677, 0.016, 0.0), vector3<double>(-0.045267402867263, 0.016569533817705, 0.0), vector3<double>(-0.371390676354105, -0.928476690885259, 0.0));
//	pick->setFunction(func1);
//	pick->define("pick");

	/*geo::Line *LineBottom = new geo::Line(sim, "bottom boundary", GEO_BOUNDARY);
	LineBottom->Define(vec3(0.0, 0.0, 0.0), vec3(0.02, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
	geo::Line *LineLeft = new geo::Line(sim, "left boundary", GEO_BOUNDARY);
	LineLeft->Define(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.02, 0.0), vec3(1.0, 0.0, 0.0));
	geo::Line *LineRight = new geo::Line(sim, "right boundary", GEO_BOUNDARY);
	LineRight->Define(vec3(0.02, 0.0, 0.0), vec3(0.02, 0.02, 0.0), vec3(-1.0, 0.0, 0.0));
	geo::Line *LineUpper = new geo::Line(sim, "upper boundary", GEO_BOUNDARY);
	LineUpper->Define(vec3(0.0, 0.02, 0.0), vec3(0.02, 0.02, 0.0), vec3(0.0, -1.0, 0.0));*/

	geo::Cube *cube = new geo::Cube(sim, "cube", GEO_BOUNDARY);
	//specimen->Define(vec2(0.0, 0.0), vec2(0.08, 0.04));
	//cube->Define(vector3<double>(0.0, -0.0096, -0.01), vector3<double>(0.02, 0.0, 0.01));
	cube->Define(vector3<double>(0.0, -0.04, -0.04), vector3<double>(0.12, 0.0, 0.04));
	geo::Shape *pick = new geo::Shape(sim, "pick", GEO_MOVING_BODY);
	pick->Define("C:/C++/case/dem/pick.dat", vector3<double>(0.0,-0.001,0.0), TUNGSTEN_CARBIDE);
	pick->setFunction(func1);
	utility::writer::SaveGeometry();

	if (!sim->Initialize()){
		std::cout << "ERROR : Initialize is failed." << std::endl;
	}
	/*pick->OnUpdateProcess();
	LineLeft->OffContact();
	LineRight->OffContact();
	LineUpper->OffContact();*/
	//LineBottom->OffContact();
	cube->OffContact();
	pick->UpdateProcess(true);
	if (!sim->RockRunCycle(1000000, 500)){
		std::cout << "ERROR : Be interrupt cycle." << std::endl;
	}
	delete sim;
	return 0;
}