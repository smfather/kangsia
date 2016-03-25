#ifndef OBJECT_H
#define OBJECT_H

#ifndef QT_OPENGL_ES_2
#include <gl/glew.h>
#include <gl/glu.h>
#endif

#include <QTextStream>
#include <QObject>
#include <QMessageBox>
#include <QFile>
#include <map>
#include "types.h"
#include "modeler.h"
#include "colors.h"
#include "algebra.h"
#include "contactConstant.h"

using namespace algebra;

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QLabel;
QT_END_NAMESPACE



#define PI		3.14159265358979323846

//inline float frand() { return rand() / (float)RAND_MAX; }

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
		enum DIALOGTYPE{ NEW_OBJECT, MODIFY_OBJECT, INFO_OBJECT};
		enum ObjectRoll{ ROLL_BOUNDARY = 0, ROLL_PARTICLE, ROLL_MOVING };
		Object(geometry_type gt=NO_GEOMETRY_TYPE);
		//Object(std::map<QString, Object*> *_objs);
		virtual ~Object() 
		{ 
			count--; 
			//if (CBMaterial) delete CBMaterial; CBMaterial = NULL;
		}
		virtual bool callDialog(DIALOGTYPE dt = NEW_OBJECT) = 0;
		virtual void draw(GLenum eMode) = 0;
		virtual void SaveObject(QTextStream& out) = 0;
		virtual void updateDataFromFile(QFile& pf, unsigned int fdtype) = 0;
		virtual void saveCurrentData(QFile& pf) = 0;
		virtual void hertzian_contact_force(void* p, void* v, void* w, void* f, void* m, float ma, float dt, contactConstant* cc) = 0;

		int ID() { return count; }
		void allocMass();
		void setMassPointer(mass* _ms) { ms = _ms; }
		void setName(QString& _n) { name = _n; }
		void setType(geometry_type gt) { type = gt;  }
		void SetHide(bool h) { isHide = h; }
		void SetRoll(ObjectRoll r) { roll = r; }
		geometry_type Type() { return type; }
		QString Name() { return name; }
		mass* Mass_ptr() { return ms;  }
		material_type MaterialType() { return mtype; }
		cmaterialType Material() { return material; }
		colors::color_type GetColor() { return ctype; }
		bool Hide() { return isHide; }
		ObjectRoll Roll() { return roll; }
		static void msgBox(QString ch, QMessageBox::Icon ic);

	protected:
		ObjectRoll roll;
		colors::color_type ctype;
		geometry_type type;
		material_type mtype;
		cmaterialType material;
		//virtual bool define(void* tg = 0) = 0;
		void colorRamp(float t, float *r);
		float lerp(float a, float b, float t){ return a + t*(b - a); }
		bool checkParameter3(QLineEdit *le);
		
		float color[4];
		QString name;
		QLineEdit *LEName;
		mass* ms;
		bool isDefined;
		static std::map<QString, parview::Object*> *objs;
		QLabel *LMaterial;
	    QComboBox *CBMaterial;
		bool isDialogOk;
		bool isHide;

		protected slots:
		virtual void Click_ok() = 0;
		virtual void Click_cancel() = 0;


	private:
		static int count;

// 	signals:
// 		void mySignal();
	};
}

#endif