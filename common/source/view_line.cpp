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
	vector3<double> sp;
	vector3<double> ep;

	pf.read((char*)&sp, sizeof(vector3<double>));
	pf.read((char*)&ep, sizeof(vector3<double>));

	startPoint = vector3<float>(
		static_cast<float>(sp.x),
		static_cast<float>(sp.y),
		static_cast<float>(sp.z));
	endPoint = vector3<float>(
		static_cast<float>(ep.x),
		static_cast<float>(ep.y),
		static_cast<float>(ep.z));
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
		glVertex3f(startPoint.x, startPoint.y, startPoint.z);
		glVertex3f(endPoint.x, endPoint.y, endPoint.z);
	}
	glEnd();
	glEndList();
}

void line::saveCurrentData(QFile& pf)
{

}