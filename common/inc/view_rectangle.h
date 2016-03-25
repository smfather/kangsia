#ifndef VIEW_RECTANGLE_H
#define VIEW_RECTANGLE_H

#include "Object.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

namespace parview
{
	class rectangle : public Object
	{
	public:
		rectangle();
		virtual ~rectangle();

		void setRectangleData(QFile& pf, unsigned int fdtype);
		void SetFromFile(QTextStream& in);
		virtual bool callDialog(DIALOGTYPE dt = NEW_OBJECT);
		virtual void draw(GLenum eMode);
		bool define(void* tg = 0);
		virtual void SaveObject(QTextStream& out);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf, unsigned int fdtype){}
		virtual void hertzian_contact_force(void* p, void* v, void* w, void* f, void* m, float ma, float dt, parview::contactConstant* cc);
		void SetDataFromFile(QTextStream& in);
		vector3<float> points[4];

		QDialog *rectDialog;
		QLineEdit *LEPa;
		QLineEdit *LEPb;
		QLineEdit *LEPc;
		QLineEdit *LEPd;

		vector3<float> u1;
		vector3<float> u2;
		vector3<float> uw;
		vector3<float> xw;
		vector3<float> pa;
		vector3<float> pb;
		float l1, l2;

		unsigned int glList;
		static unsigned int nRect;

	private slots:
		void Click_ok();
		void Click_cancel();
	};
}

#endif