#include "Object.h"
#include "view_mass.h"
#include <QStringList>
#include <QLineEdit>
#include <QMessageBox>

using namespace parview;

int Object::count = -1;
std::map<QString, parview::Object*> *Object::objs = NULL;

Object::Object(geometry_type gt)
	: ms(NULL)
	, type(gt)
	, isDefined(false)
{
	count++;
	color[0] = colors[count * 4 + 0];
	color[1] = colors[count * 4 + 1];
	color[2] = colors[count * 4 + 2];
	color[3] = colors[count * 4 + 3];
}

// Object::Object(std::map<QString, Object*> *_objs)
// 	: ms(NULL)
// 	, isDefined(false)
// 	, objs(_objs)
// {
// 	count++;
// 	color[0] = colors[count * 4 + 0];
// 	color[1] = colors[count * 4 + 1];
// 	color[2] = colors[count * 4 + 2];
// 	color[3] = colors[count * 4 + 3];
// }

void Object::allocMass()
{
	ms = new mass;
}

void Object::colorRamp(float t, float *r)
{
	//const int ncolors = 7;
	///*float c[ncolors][3] = {
	//	{ 1.0, 0.0, 0.0, },
	//	{ 1.0, 0.5, 0.0, },
	//	{ 1.0, 1.0, 0.0, },
	//	{ 0.0, 1.0, 0.0, },5
	//	{ 0.0, 1.0, 1.0, },
	//	{ 0.0, 0.0, 1.0, },
	//	{ 1.0, 0.0, 1.0, },
	//};*/
	//float c[ncolors][3] = {
	//	{ 1.0, 0.0, 1.0, },
	//	{ 0.0, 0.0, 1.0, },
	//	{ 0.0, 1.0, 1.0, },
	//	{ 0.0, 1.0, 0.0, },
	//	{ 1.0, 1.0, 0.0, },
	//	{ 1.0, 0.5, 1.0, },
	//	{ 1.0, 0.0, 0.0, },
	//};
	//t = t * (ncolors - 1);
	//int i = (int)t;
	//float u = t - floor(t);
	//r[0] = lerp(c[i][0], c[i + 1][0], u);
	//r[1] = lerp(c[i][1], c[i + 1][1], u);
	//r[2] = lerp(c[i][2], c[i + 1][2], u);
	double div255 = 1.0 / 255.0;
	const int ncolors = 9;
	/*float c[ncolors][3] = {
	{ 1.0, 0.0, 0.0, },
	{ 1.0, 0.5, 0.0, },
	{ 1.0, 1.0, 0.0, },
	{ 0.0, 1.0, 0.0, },5
	{ 0.0, 1.0, 1.0, },
	{ 0.0, 0.0, 1.0, },
	{ 1.0, 0.0, 1.0, },
	};*/
	float c[ncolors][3] = {
		{ 3 * div255, 0.0, 102 * div255, },
		{ 0 * div255, 84 * div255, 1.0, },
		{ 0.0, 216.0 * div255, 1.0, },
		{ 29.0 * div255, 219.0 * div255, 22.0 * div255, },
		{ 171.0 * div255, 242 * div255, 0.0, },
		{ 1.0, 228.0 * div255, 0.0, },
		{ 1.0, 187 * div255, 0.0, },
		{ 1.0, 94.0 * div255, 0.0, },
		{ 1.0, 0.0, 0.0 }
	};
	/*t = t * (ncolors - 1);
	int i = (int)t;
	float u = t - floor(t);*/
	int i = (int)t;
	if (i < 0 || i > 9){
	r[0] = 1.0;
	r[1] = 0.0;
	r[2] = 0.0; return;
}
	r[0] = c[i][0];
	r[1] = c[i][1];
	r[2] = c[i][2];
	//r[0] = lerp(c[i][0], c[i + 1][0], u);
	//r[1] = lerp(c[i][1], c[i + 1][1], u);5
	//r[2] = lerp(c[i][2], c[i + 1] [2], u);
}

bool Object::checkParameter3(QLineEdit *le)
{
	QStringList strList = le->text().split(" ");
	if (strList.size() != 3){
		le->setStyleSheet("QLineEdit{background: yellow};");
		return false;
	}
	else{
		le->setStyleSheet("QLineEdit{background: white};");
		return true;
	}
}

void Object::msgBox(QString ch, QMessageBox::Icon ic)
{
	QMessageBox msg;
	msg.setIcon(ic);
	msg.setText(ch);
	msg.exec();
}