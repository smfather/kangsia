#include "view_rectangle.h"
#include <QtWidgets>

using namespace parview;

unsigned int rectangle::nRect = 0;

rectangle::rectangle()
	: rectDialog(NULL)
{

}

rectangle::~rectangle()
{

}

void rectangle::SetFromFile(QTextStream& in)
{
	type = RECTANGLE;
	in >> name;
	in >> points[0].x >> points[0].y >> points[0].z
		>> points[1].x >> points[1].y >> points[1].z
		>> points[2].x >> points[2].y >> points[2].z
		>> points[3].x >> points[3].y >> points[3].z;
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

bool rectangle::callDialog(DIALOGTYPE dt)
{
	QString nm;
	if (!rectDialog)
	{
		QTextStream(&nm) << "Rect_" << nRect;
		rectDialog = new QDialog;
		QLabel *LName = new QLabel("Name");
		QLabel *LPa = new QLabel("Point a");
		QLabel *LPb = new QLabel("Point b");
		QLabel *LPc = new QLabel("Point c");
		QLabel *LPd = new QLabel("Point d");
		LEName = new QLineEdit(nm);
		LEPa = new QLineEdit;
		LEPb = new QLineEdit;
		LEPc = new QLineEdit;
		LEPd = new QLineEdit;
		QGridLayout *rectLayout = new QGridLayout;
		QPushButton *PBOk = new QPushButton("OK");
		QPushButton *PBCancel = new QPushButton("Cancel");
		connect(PBOk, SIGNAL(clicked()), this, SLOT(Click_ok()));
		connect(PBCancel, SIGNAL(clicked()), this, SLOT(Click_cancel()));
		rectLayout->addWidget(LMaterial, 0, 0);
		rectLayout->addWidget(CBMaterial, 0, 1, 1, 2);
		rectLayout->addWidget(LName, 1, 0);		rectLayout->addWidget(LEName, 1, 1, 1, 2);
		rectLayout->addWidget(LPa, 2, 0);		rectLayout->addWidget(LEPa, 2, 1, 1, 2);
		rectLayout->addWidget(LPb, 3, 0);		rectLayout->addWidget(LEPb, 3, 1, 1, 2);
		rectLayout->addWidget(LPc, 4, 0);		rectLayout->addWidget(LEPc, 4, 1, 1, 2);
		rectLayout->addWidget(LPd, 5, 0);		rectLayout->addWidget(LEPd, 5, 1, 1, 2);
		rectLayout->addWidget(PBOk, 6, 0);
		rectLayout->addWidget(PBCancel, 6, 1);
		rectDialog->setLayout(rectLayout);
	}
	else{
		LEPa->text().clear();
		LEPb->text().clear();
		LEPc->text().clear();
		LEPd->text().clear();
		QTextStream(&nm) << "Rect_" << nRect;
	}
	rectDialog->exec();
	return isDialogOk ? true : false;
}

void rectangle::Click_ok()
{
	if (LEPa->text().isEmpty() || LEPb->text().isEmpty() || LEPc->text().isEmpty() || LEPd->text().isEmpty()){
		msgBox("There is empty data!!", QMessageBox::Critical);
		return;
	}
	
	QStringList ss;// = LEPa->text().split(",");
	if (LEPa->text().split(",").size() == 3)
		ss = LEPa->text().split(",");
	else
		if (LEPa->text().split(" ").size() == 3)
			ss = LEPa->text().split(" ");
		else
			if (LEPa->text().split(", ").size() == 3)
				ss = LEPa->text().split(", ");
			else {
				msgBox("Point a is wrong data.", QMessageBox::Critical);
				return;
			}
	points[0].x = ss.at(0).toFloat(); points[0].y = ss.at(1).toFloat(); points[0].z = ss.at(2).toFloat();

	if (LEPb->text().split(",").size() == 3)
		ss = LEPb->text().split(",");
	else
		if (LEPb->text().split(" ").size() == 3)
			ss = LEPb->text().split(" ");
		else
			if (LEPb->text().split(", ").size() == 3)
				ss = LEPb->text().split(", ");
			else{
				msgBox("Point b is wrong data.", QMessageBox::Critical);
				return;
			}
	points[1].x = ss.at(0).toFloat(); points[1].y = ss.at(1).toFloat(); points[1].z = ss.at(2).toFloat();

	if (LEPc->text().split(",").size() == 3)
		ss = LEPc->text().split(",");
	else
		if (LEPc->text().split(" ").size() == 3)
			ss = LEPc->text().split(" ");
		else
			if (LEPc->text().split(", ").size() == 3)
				ss = LEPc->text().split(", ");
			else{
				msgBox("Point c is wrong data.", QMessageBox::Critical);
				return;
			}
	points[2].x = ss.at(0).toFloat(); points[2].y = ss.at(1).toFloat(); points[2].z = ss.at(2).toFloat();

	if (LEPd->text().split(",").size() == 3)
		ss = LEPd->text().split(",");
	else
		if (LEPd->text().split(" ").size() == 3)
			ss = LEPd->text().split(" ");
		else
			if (LEPd->text().split(", ").size() == 3)
				ss = LEPd->text().split(", ");
			else{
				msgBox("Point d is wrong data.", QMessageBox::Critical);
				return;
			}
	points[3].x = ss.at(0).toFloat(); points[3].y = ss.at(1).toFloat(); points[3].z = ss.at(2).toFloat();

	mtype = material_str2enum(CBMaterial->currentText().toStdString());
	material = getMaterialConstant(mtype);

	name = LEName->text();

	nRect++;
	rectDialog->close();
	delete rectDialog; rectDialog = NULL;
	isDialogOk = true;
}

void rectangle::Click_cancel()
{
	rectDialog->close();
	delete rectDialog; rectDialog = NULL;
	isDialogOk = false;
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

bool rectangle::define(void* tg)
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

	xw = vector3<float>(points[0].x, points[0].y, points[0].z);
	pa = vector3<float>(points[1].x, points[1].y, points[1].z) - xw;
	pb = vector3<float>(points[3].x, points[3].y, points[3].z) - xw;
	l1 = pa.length();
	l2 = pb.length();
	u1 = pa / l1;
	u2 = pb / l2;
	uw = u1.cross(u2);

	return true;
}

void rectangle::saveCurrentData(QFile& pf)
{

}

void rectangle::SaveObject(QTextStream& out)
{
	out << "OBJECT" << " " << "RECTANGLE" << " " << name << " " << (int)roll << "\n";
	out << (int)mtype << "\n";
	out << points[0].x << " " << points[0].y << " " << points[0].z << "\n";
	out << points[1].x << " " << points[1].y << " " << points[1].z << "\n";
	out << points[2].x << " " << points[2].y << " " << points[2].z << "\n";
	out << points[3].x << " " << points[3].y << " " << points[3].z << "\n";
}

void rectangle::hertzian_contact_force(void* p, void* v, void* w, void* f, void* m, float ma, float dt, parview::contactConstant* cc)
{
	vector4<float>* pos = (vector4<float>*)p;
	vector4<float>* vel = (vector4<float>*)v;
	vector4<float>* omega = (vector4<float>*)w;
	vector3<float>* force = (vector3<float>*)f;
	vector3<float>* moment = (vector3<float>*)m;

	vector3<float> single_force;
	vector3<float> dp = vector3<float>(pos->x, pos->y, pos->z) - xw;
	vector3<float> wp = vector3<float>(dp.dot(u1), dp.dot(u2), dp.dot(uw));
	contact_coefficient_t c = cc->CalcContactCoefficient(pos->w, 0.f, ma, 0.f);
	if (abs(wp.z) < pos->w && (wp.x > 0 && wp.x < l1) && (wp.y > 0 && wp.y < l2)){
		vector3<float> uu = uw / uw.length();
		float pp = -sign(dp.dot(uw));
		vector3<float> unit = pp * uu;
		float collid_dist = pos->w - abs(dp.dot(unit));
		vector3<float> dv = -(vel->toVector3() + omega->toVector3().cross(pos->w * unit));
		single_force = (-c.kn * pow(collid_dist, 1.5) + c.vn * dv.dot(unit)) * unit;
		vector3<float> e = dv - dv.dot(unit) * unit;
		float mag_e = e.length();
		if (mag_e){
			vector3<float> s_hat = e / mag_e;
			float ds = mag_e * dt;
			vector3<float> shear_force = MIN(c.ks * ds + c.vs * dv.dot(s_hat), c.mu * single_force.length()) * s_hat;
			(*moment) += (pos->w * unit).cross(shear_force);
		}
		(*force) += single_force;
	}
}