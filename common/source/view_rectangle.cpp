#include "view_rectangle.h"

using namespace parview;

rectangle::rectangle()
{

}

rectangle::~rectangle()
{

}

void rectangle::setRectangleData(QFile& pf, unsigned int fdtype)
{
	type = RECTANGLE;
	int name_size = 0;
	char nm[256] = { 0, };
	pf.read((char*)&name_size, sizeof(int));
	pf.read((char*)nm, sizeof(char)*name_size);
	name.sprintf("%s", nm);
	
	if (fdtype == 4){
		vector3<float> ps[4];
		pf.read((char*)ps, sizeof(vector3<float>) * 4);
		points[0] = vector3<float>(ps[0].x, ps[0].y, ps[0].z);
		points[1] = vector3<float>(ps[1].x, ps[1].y, ps[1].z);
		points[2] = vector3<float>(ps[2].x, ps[2].y, ps[2].z);
		points[3] = vector3<float>(ps[3].x, ps[3].y, ps[3].z);
	}
	else{
		vector3<double> ps[4];
		pf.read((char*)ps, sizeof(vector3<double>) * 4);
		points[0] = vector3<float>(
			static_cast<float>(ps[0].x),
			static_cast<float>(ps[0].y),
			static_cast<float>(ps[0].z));
		points[1] = vector3<float>(
			static_cast<float>(ps[1].x),
			static_cast<float>(ps[1].y),
			static_cast<float>(ps[1].z));
		points[2] = vector3<float>(
			static_cast<float>(ps[2].x),
			static_cast<float>(ps[2].y),
			static_cast<float>(ps[2].z));
		points[3] = vector3<float>(
			static_cast<float>(ps[3].x),
			static_cast<float>(ps[3].y),
			static_cast<float>(ps[3].z));
	}
}

void rectangle::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3fv(Object::color);
	glCallList(glList);
	glPopMatrix();
}

void rectangle::define(void* tg)
{
	glList = glGenLists(1);
	glNewList(glList, GL_COMPILE);
	glShadeModel(GL_SMOOTH);
	//glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_LINE_STRIP);
	{
		glVertex3f(points[0].x, points[0].y, points[0].z);
		glVertex3f(points[1].x, points[1].y, points[1].z);
		glVertex3f(points[2].x, points[2].y, points[2].z);
		glVertex3f(points[3].x, points[3].y, points[3].z);
		glVertex3f(points[0].x, points[0].y, points[0].z);
	}
	glEnd();
	glEndList();
}

void rectangle::saveCurrentData(QFile& pf)
{

}