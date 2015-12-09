#ifndef OBJECT_H
#define OBJECT_H

#ifndef QT_OPENGL_ES_2
#include <gl/glew.h>
#include <gl/glu.h>
#endif

#include <QObject>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <map>
#include "types.h"
#include "algebra/vector.hpp"
#include "algebra/vector3.hpp"

using namespace algebra;

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QLabel;
QT_END_NAMESPACE

#define MAX_FRAME	2000
#define PI		3.14159265358979323846

inline float frand() { return rand() / (float)RAND_MAX; }

namespace parview
{
	static float colors[16] = { 1, 0, 0, 0
							  , 0, 1, 0, 0
							  , 0, 0, 1, 0
							  , 1, 1, 0, 0 };
	class mass;

	class Object : public QObject
	{
		Q_OBJECT

	public:
		Object(geometry_type gt=NO_GEOMETRY_TYPE);
		//Object(std::map<QString, Object*> *_objs);
		virtual ~Object() 
		{ 
			count--; 
			//if (CBMaterial) delete CBMaterial; CBMaterial = NULL;
		}
		virtual void callDialog() = 0;
		virtual void draw() = 0;
		virtual void updateDataFromFile(QFile& pf, unsigned int fdtype) = 0;
		virtual void saveCurrentData(QFile& pf) = 0;

		void allocMass();
		void setMassPointer(mass* _ms) { ms = _ms; }
		void setName(QString& _n) { name = _n; }
		void setType(geometry_type gt) { type = gt;  }
		geometry_type Type() { return type; }
		QString Name() { return name; }
		mass* Mass_ptr() { return ms;  }
		cmaterialType Material() { return material; }

	protected:
		geometry_type type;
		material_type mtype;
		cmaterialType material;
		virtual void define(void* tg = 0) = 0;
		void colorRamp(float t, float *r);
		float lerp(float a, float b, float t){ return a + t*(b - a); }
		bool checkParameter3(QLineEdit *le);
		void msgBox(QString ch, QMessageBox::Icon ic);
		float color[4];
		QString name;
		mass* ms;
		bool isDefined;
		static std::map<QString, parview::Object*> *objs;
		QLabel *LMaterial;
	    QComboBox *CBMaterial;

	private:
		static int count;

	signals:
		void mySignal();
	};
}

#endif