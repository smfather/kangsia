#ifndef VIEW_CUBE_H
#define VIEW_CUBE_H

#include "Object.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
class QGridLayout;
class QRadioButton;
QT_END_NAMESPACE

namespace parview
{
	class cube : public Object
	{
		Q_OBJECT

	public:
		cube();
		cube(std::map<QString, Object*> *_objs);
		virtual ~cube() {}
		virtual bool callDialog(DIALOGTYPE dt = NEW_OBJECT);
		virtual void draw();
		virtual void SaveObject(QTextStream& out) {}
		bool define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf, unsigned int fdtype){}
		virtual void hertzian_contact_force(void* p, void* v, void* w, void* f, void* m, float ma, float dt, parview::contactConstant* cc){}

		float* getVertice() { return vertice; }
		float* getMaxPoint() { return maxPoint; }
		float* getMinPoint() { return minPoint; }

		unsigned int glList;
		float width;
		float depth;
		float height;
		int indice[24];
		float vertice[24];
		float origin[3];
		float maxPoint[3];
		float minPoint[3];

		static unsigned int nCube;

		QDialog *cubeDialog;
		QLabel *LStartPoint;
		QLabel *LEndPoint;
		QLabel *LName;
		QLineEdit *LEName;
		QLineEdit *LEStartPoint;
		QLineEdit *LEEndPoint;
		QGridLayout *cubeLayout;
		QPushButton *PBOk;
		QPushButton *PBCancel;

		private slots:
		virtual void Click_ok();
		virtual void Click_cancel();
	};
}

#endif