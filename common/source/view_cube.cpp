#include "view_cube.h"
#include <QtWidgets>

using namespace parview;


unsigned int parview::cube::nCube = 0;
// QDialog *parview::cube::cubeDialog = NULL;
// QLabel *parview::cube::LStartPoint = NULL;
// QLabel *parview::cube::LEndPoint = NULL;
// QLabel *parview::cube::LName = NULL;
// QLineEdit *parview::cube::LEName = NULL;
// QLineEdit *parview::cube::LEStartPoint = NULL;
// QLineEdit *parview::cube::LEEndPoint = NULL;
// QGridLayout *parview::cube::cubeLayout = NULL;
// QPushButton *parview::cube::PBOk = NULL;
// QPushButton *parview::cube::PBCancel = NULL;


cube::cube() : Object(CUBE), cubeDialog(NULL)
{
	indice[0] = 0; indice[1] = 2; indice[2] = 4; indice[3] = 6;
	indice[4] = 1; indice[5] = 3; indice[6] = 2; indice[7] = 0;
	indice[8] = 5; indice[9] = 7; indice[10] = 6; indice[11] = 4;
	indice[12] = 3; indice[13] = 5; indice[14] = 4; indice[15] = 2;
	indice[16] = 7; indice[17] = 1; indice[18] = 0; indice[19] = 6;
	indice[20] = 1; indice[21] = 7; indice[22] = 5; indice[23] = 3;

	maxPoint[0] = 0; maxPoint[1] = 0; maxPoint[2] = 0;
	minPoint[0] = 0; minPoint[1] = 0; minPoint[2] = 0;
}

cube::cube(std::map<QString, Object*> *_objs) : Object()
{
	indice[0] = 0; indice[1] = 2; indice[2] = 4; indice[3] = 6;
	indice[4] = 1; indice[5] = 3; indice[6] = 2; indice[7] = 0;
	indice[8] = 5; indice[9] = 7; indice[10] = 6; indice[11] = 4;
	indice[12] = 3; indice[13] = 5; indice[14] = 4; indice[15] = 2;
	indice[16] = 7; indice[17] = 1; indice[18] = 0; indice[19] = 6;
	indice[20] = 1; indice[21] = 7; indice[22] = 5; indice[23] = 3;

	maxPoint[0] = 0; maxPoint[1] = 0; maxPoint[2] = 0;
	minPoint[0] = 0; minPoint[1] = 0; minPoint[2] = 0;
	Object::objs = _objs;
}

void cube::draw()
{
	if (isDefined){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3fv(Object::color);
		glCallList(glList);
		glPopMatrix();
	}
}

bool cube::define(void* tg)
{
	glList = glGenLists(1);
	glNewList(glList, GL_COMPILE);
	glShadeModel(GL_SMOOTH);
	//glColor3f(0.0f, 0.0f, 1.0f);
	
	glBegin(GL_QUADS);
	for (int i(0); i < 6; i++){
		int *id = &indice[i * 4];
		glVertex3f(vertice[id[3] * 3 + 0], vertice[id[3] * 3 + 1], vertice[id[3] * 3 + 2]);
		glVertex3f(vertice[id[2] * 3 + 0], vertice[id[2] * 3 + 1], vertice[id[2] * 3 + 2]);
		glVertex3f(vertice[id[1] * 3 + 0], vertice[id[1] * 3 + 1], vertice[id[1] * 3 + 2]);
		glVertex3f(vertice[id[0] * 3 + 0], vertice[id[0] * 3 + 1], vertice[id[0] * 3 + 2]);
	}

	glEnd();
	glEndList();

	isDefined = true;
	return true;
}

void cube::saveCurrentData(QFile& pf)
{
	if (!ms)
		return;
}

bool cube::callDialog(DIALOGTYPE dt)
{
	if (!cubeDialog){
		cubeDialog = new QDialog;
		LName = new QLabel("Name");
		LStartPoint = new QLabel("Start point");
		LEndPoint = new QLabel("End point");
		LEName = new QLineEdit;
		LEStartPoint = new QLineEdit;
		LEEndPoint = new QLineEdit;
		cubeLayout = new QGridLayout;
		PBOk = new QPushButton("OK");
		PBCancel = new QPushButton("Cancel");
		connect(PBOk, SIGNAL(clicked()), this, SLOT(Click_ok()));
		connect(PBCancel, SIGNAL(clicked()), this, SLOT(Click_cancel()));
		cubeLayout->addWidget(LMaterial, 0, 0);
		cubeLayout->addWidget(CBMaterial, 0, 1, 1, 2);
		cubeLayout->addWidget(LName, 1, 0);
		cubeLayout->addWidget(LEName, 1, 1, 1, 2);
		cubeLayout->addWidget(LStartPoint, 2, 0);
		cubeLayout->addWidget(LEStartPoint, 2, 1, 1, 2);
		cubeLayout->addWidget(LEndPoint, 3, 0);
		cubeLayout->addWidget(LEEndPoint, 3, 1, 1, 2);
		cubeLayout->addWidget(PBOk, 4, 0);
		cubeLayout->addWidget(PBCancel, 4, 1);
		cubeDialog->setLayout(cubeLayout);
	}
	LEName->text().clear();
	LEStartPoint->text().clear();
	LEEndPoint->text().clear();
	cubeDialog->exec();
// 	cubeDialog->show();
// 	cubeDialog->raise();
// 	cubeDialog->activateWindow();
	return isDialogOk ? true : false;
}

void cube::Click_ok()
{
	if (LEStartPoint->text().isEmpty()){
		msgBox("Value of start point is empty!!", QMessageBox::Critical);
	}
	else if (LEEndPoint->text().isEmpty()){
		msgBox("Value of end point is empty!!", QMessageBox::Critical);
	}

	if (!checkParameter3(LEStartPoint)){
		msgBox("Start point is wrong data.", QMessageBox::Critical);
		return;
	}
	else if (!checkParameter3(LEEndPoint)){
		msgBox("End point is wrong data.", QMessageBox::Critical);
		return;
	}

	Object::name = LEName->text();
	mtype = material_str2enum(CBMaterial->currentText().toStdString());
	material = getMaterialConstant(mtype);

	QStringList chList = LEStartPoint->text().split(" ");
	minPoint[0] = chList.at(0).toFloat();
	minPoint[1] = chList.at(1).toFloat();
	minPoint[2] = chList.at(2).toFloat();

	chList = LEEndPoint->text().split(" ");
	maxPoint[0] = chList.at(0).toFloat();
	maxPoint[1] = chList.at(1).toFloat();
	maxPoint[2] = chList.at(2).toFloat();

	width = maxPoint[0] - minPoint[0];
	height = maxPoint[1] - minPoint[1];
	depth = maxPoint[2] - minPoint[2];

	vertice[0] =  minPoint[0];		   vertice[1] =  minPoint[1];		   vertice[2] = minPoint[2];
	vertice[3] =  minPoint[0];		   vertice[4] =  minPoint[1] + height; vertice[5] = minPoint[2];
	vertice[6] =  minPoint[0];		   vertice[7] =  minPoint[1];		   vertice[8] = minPoint[2] + depth;
	vertice[9] =  minPoint[0];		   vertice[10] = minPoint[1] + height; vertice[11] = minPoint[2] + depth;
	vertice[12] = minPoint[0] + width; vertice[13] = minPoint[1];		   vertice[14] = minPoint[2] + depth;
	vertice[15] = minPoint[0] + width; vertice[16] = minPoint[1] + height; vertice[17] = minPoint[2] + depth;
	vertice[18] = minPoint[0] + width; vertice[19] = minPoint[1];		   vertice[20] = minPoint[2];
	vertice[21] = minPoint[0] + width; vertice[22] = minPoint[1] + height; vertice[23] = minPoint[2];

	cubeDialog->close();

	delete cubeDialog;
	cubeDialog = NULL;
	isDialogOk = true;
}

void cube::Click_cancel()
{
	delete cubeDialog;
	cubeDialog = NULL;
	isDialogOk = false;
}