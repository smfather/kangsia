#include "solveDialog.h"
#include "glwidget.h"
#include "DEM/DemSimulation.h"
#include "view_particles.h"
#include <QtWidgets>
#include <map>


using namespace parview;

solveDialog::solveDialog()
	: isDialogOk(false)
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

bool solveDialog::callDialog()
{
	if (!solveDlg){
		solveDlg = new QDialog;
		QLabel *LWorldOrigin = new QLabel("World origin");
		QLabel *LGridSize = new QLabel("Grid size");
		QLabel *LCaseName = new QLabel("Case name");
		QLabel *LBasePath = new QLabel("Base path");
		QLabel *LSimTime = new QLabel("Simulation time");
		QLabel *LTimeStep = new QLabel("Time step");
		QLabel *LSaveStep = new QLabel("Save step");
		LEWorldOrigin = new QLineEdit;
		LEGridSize = new QLineEdit;
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
		solveLayout->addWidget(LWorldOrigin, 5, 0);
		solveLayout->addWidget(LEWorldOrigin, 5, 1, 1,2);
		solveLayout->addWidget(LGridSize, 6, 0);
		solveLayout->addWidget(LEGridSize, 6, 1, 1, 2);
		solveLayout->addWidget(PBSolve, 7, 0);
		solveLayout->addWidget(PBCancel, 7, 1);
		solveDlg->setLayout(solveLayout);

		connect(PBSolve, SIGNAL(clicked()), this, SLOT(Click_Solve()));
		connect(PBCancel, SIGNAL(clicked()), this, SLOT(Click_Cancel()));

		LEBasePath->setText("C:/C++/result");
		LECaseName->setText("Model_1");
		LESimTime->setText("1.0");
		LETimeStep->setText("1e-5");
		LESaveStep->setText("100");
		LEWorldOrigin->setText("0.0, 0.0, 0.0");
		LEGridSize->setText("128, 128, 128");
	}
	solveDlg->exec();
	return isDialogOk ? true : false;
}

void solveDialog::Click_Solve()
{
	simTime = LESimTime->text().toFloat();
	timeStep = LETimeStep->text().toFloat();
	saveTime = LESaveStep->text().toFloat();
	caseName = LECaseName->text();
	basePath = LEBasePath->text();
// 
// 	QStringList ss;
// 	if (LEWorldOrigin->text().split(",").size() == 3)
// 		ss = LEWorldOrigin->text().split(",");
// 	else
// 		if (LEWorldOrigin->text().split(" ").size() == 3)
// 			ss = LEWorldOrigin->text().split(" ");
// 		else
// 			if (LEWorldOrigin->text().split(", ").size() == 3)
// 				ss = LEWorldOrigin->text().split(", ");
// 			else {
// 				Object::msgBox("World origin is wrong data.", QMessageBox::Critical);
// 				return;
// 			}
// 	worldOrigin.x = ss.at(0).toFloat(); worldOrigin.y = ss.at(1).toFloat(); worldOrigin.z = ss.at(2).toFloat();
// 
// 	if (LEGridSize->text().split(",").size() == 3)
// 		ss = LEGridSize->text().split(",");
// 	else
// 		if (LEGridSize->text().split(" ").size() == 3)
// 			ss = LEGridSize->text().split(" ");
// 		else
// 			if (LEGridSize->text().split(", ").size() == 3)
// 				ss = LEGridSize->text().split(", ");
// 			else {
// 				Object::msgBox("Grid size is wrong data.", QMessageBox::Critical);
// 				return;
// 			}
// 	gridSize.x = ss.at(0).toUInt(); gridSize.y = ss.at(1).toUInt(); gridSize.z = ss.at(2).toUInt();

	solveDlg->close();
	delete solveDlg; solveDlg = NULL;
	isDialogOk = true;
}

void solveDialog::Click_Cancel()
{
	solveDlg->close();
	delete solveDlg; solveDlg = NULL;
	isDialogOk = false;
}