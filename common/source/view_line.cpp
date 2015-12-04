#include "view_line.h"

using namespace parview;

line::line()
{

}

line::~line()
{

}

void line::setLineData(QFile& pf)
{
	type = LINE;
	int name_size = 0;
	char nm[256] = { 0, };
	pf.read((char*)&name_size, sizeof(int));
	pf.read((char*)nm, sizeof(char)*name_size);
	name.sprintf("%s", nm);
	double sp[3];
	double ep[3];

	pf.read((char*)&sp, sizeof(double)*3);
	pf.read((char*)&ep, sizeof(double)*3);

	startPoint[0] = static_cast<float>(sp[0]);
	startPoint[1] = static_cast<float>(sp[1]);
	startPoint[2] = static_cast<float>(sp[2]);

	endPoint[0] = static_cast<float>(ep[0]);
	endPoint[1] = static_cast<float>(ep[1]);
	endPoint[2] = static_cast<float>(ep[2]);
}

void line::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3fv(Object::color);
	glCallList(glList);
	glPopMatrix();
}

void line::define(void* tg)
{
	glList = glGenLists(1);
	glNewList(glList, GL_COMPILE);
	glShadeModel(GL_SMOOTH);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	{
		glVertex3f(startPoint[0], startPoint[1], startPoint[2]);
		glVertex3f(endPoint[0], endPoint[1], endPoint[2]);
	}
	glEnd();
	glEndList();
}

void line::saveCurrentData(QFile& pf)
{

}