#ifndef VIEW_PARTICLES_H
#define VIEW_PARTICLES_H

#include "Object.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QStringList;
class QPushButton;
class QLineEdit;
class QLabel;
class QComboBox;
class QGridLayout;
QT_END_NAMESPACE

namespace parview
{
	class particles : public Object
	{
		Q_OBJECT

	public:
		particles();
		virtual ~particles();

		void draw_particles();
		virtual void callDialog();
		virtual void draw();
		virtual void define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf, unsigned int fdtype);

		void alloc_buffer(QFile& pf, unsigned int n);
		void alloc_buffer_sph(QFile& pf, unsigned int n);
		void alloc_buffer_dem(QFile& pf, unsigned int n);
		
		float* getPosition(unsigned int id) { return pos[id]; }
		float* getVelocity(unsigned int id) { return vel[id]; }
		QString& Name() { return name; }
		unsigned int Np() { return np;  }
		void bindingWindowHeight(int *height) { winHeight = height; }
		algebra::vector3<float> getPositionToV3(unsigned int id);
		algebra::vector3<float> getVelocityToV3(unsigned int id);
		double getPressure(unsigned id);
		double getFreeSurfaceValue(unsigned int id);
		bool isFreeSurface(unsigned int id);
		void changeParticleColor(unsigned int id);
		void drawSupportSphere(unsigned int id);
		void AddParticlesFromFile(QFile& pf);
		void GeometryCombeBoxWidgetList(QStringList &stList) { geoComboxList = stList; }
		QString& BaseGeometryText() { return baseGeometry; }

	private:
		unsigned int createVBO(unsigned int size, float *bufferData = NULL);
		unsigned int _compileProgram(const char *vsource, const char *fsource);
		void _drawPoints();

		unsigned int m_posVBO;
		unsigned int m_colorVBO;
		unsigned int m_program;

		QString name;
		QString baseGeometry;
		int *winHeight;
		unsigned int np;
		float radius;
		float *buffer;
		float *color_buffer;
		bool *freeSurface[MAX_FRAME];
		float *freeSurfaceValue[MAX_FRAME];
		float *pos[MAX_FRAME];
		float *vel[MAX_FRAME];
		float *pressure[MAX_FRAME];
		float *color[MAX_FRAME];

		bool isDisplaySupportRadius;
		vector3<float> support_pos;

		bool isSetColor;

// 		// Qt
		QDialog *particleDialog;
		QLabel *LBaseGeometry;
		QComboBox *CBGeometry;
		QLabel *LName;
		QLineEdit *LEName;
		QLabel *LRadius;
		QLineEdit *LERadius;
// 		QLabel *LStartPoint;
// 		QLineEdit *LEStartPoint;
// 		QLabel *LEndPoint;
// 		QLineEdit *LEEndPoint;
		QGridLayout *particleLayout;
		QStringList geoComboxList;
		QPushButton *PBOk;
		QPushButton *PBCancel;
		
	private slots:
		void Click_ok();
		void Click_cancel();

	signals:
		void mySignal();
	};
}

#endif