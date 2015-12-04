#include "solveDialog.h"
#include "glwidget.h"
#include "DEM/DemSimulation.h"
#include "view_particles.h"
#include <QtWidgets>
#include <map>


using namespace parview;

solveDialog::solveDialog()
{
	solveDlg = NULL;
}

solveDialog::solveDialog(GLWidget *gl)
{
	solveDlg = NULL;
	GL = gl;
}

solveDialog::~solveDialog()
{
	if (solveDlg) delete solveDlg; solveDlg = NULL;
}

void solveDialog::callDialog()
{
	if (!solveDlg){
		solveDlg = new QDialog;
		LCaseName = new QLabel("Case name");
		LBasePath = new QLabel("Base path");
		LSimTime = new QLabel("Simulation time");
		LTimeStep = new QLabel("Time step");
		LSaveStep = new QLabel("Save step");
		LECaseName = new QLineEdit;
		LEBasePath = new QLineEdit;
		LESimTime = new QLineEdit;
		LETimeStep = new QLineEdit;
		LESaveStep = new QLineEdit;
		solveLayout = new QGridLayout;
		PBSolve = new QPushButton("Solve");
		PBCancel = new QPushButton("Cancel");
		solveLayout->addWidget(LCaseName, 0, 0);
		solveLayout->addWidget(LECaseName, 0, 1, 1, 2);
		solveLayout->addWidget(LBasePath, 1, 0);
		solveLayout->addWidget(LEBasePath, 1, 1, 1, 2);
		solveLayout->addWidget(LSimTime, 2, 0);
		solveLayout->addWidget(LESimTime, 2, 1, 1, 2);
		solveLayout->addWidget(LTimeStep, 3, 0);
		solveLayout->addWidget(LETimeStep, 3, 1, 1, 2);
		solveLayout->addWidget(LSaveStep, 4, 0);
		solveLayout->addWidget(LESaveStep, 4, 1, 1, 2);
		solveLayout->addWidget(PBSolve, 5, 0);
		solveLayout->addWidget(PBCancel, 5, 1);
		solveDlg->setLayout(solveLayout);

		connect(PBSolve, SIGNAL(clicked()), this, SLOT(Click_Solve()));
		connect(PBCancel, SIGNAL(clicked()), this, SLOT(Click_Cancel()));

		LEBasePath->setText("C:/C++/result");
		LECaseName->setText("Model_1");
		LESimTime->setText("1.0");
		LETimeStep->setText("1e-5");
		LESaveStep->setText("500");
	}
	solveDlg->exec();
}

void solveDialog::Click_Solve()
{
	solveDlg->close();
	DemSimulation *dem = new DemSimulation;
	dem->SimulationTime() = LESimTime->text().toFloat();
	dem->TimeStep() = LETimeStep->text().toFloat();
	dem->SaveStep() = LESaveStep->text().toFloat();
	//std::map<QString, parview::Object*>::iterator it = GL->Objects().find("Particles");
	//parview::particles* pars = dynamic_cast<parview::particles*>(it->second);
	dem->Initialize(GL->Objects());
}

void solveDialog::Click_Cancel()
{

}