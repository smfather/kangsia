#ifndef VIEW_PARTICLES_H
#define VIEW_PARTICLES_H

#include "Object.h"
#include "view_controller.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QStringList;
class QPushButton;
class QLineEdit;
class QLabel;
class QComboBox;
class QGridLayout;
class QTabWidget;
QT_END_NAMESPACE

namespace parview
{
	class particles : public Object
	{
		Q_OBJECT

	public:

		struct particle{
			unsigned int id;
			algebra::vector4<float> pos;
			algebra::vector4<float> vel;
			algebra::vector4<float> acc;
			algebra::vector4<float> omega;
			algebra::vector4<float> alpha;
		};

		particles();
		virtual ~particles();

		void draw_particles();
		virtual bool callDialog(DIALOGTYPE dt = NEW_OBJECT);
		virtual void draw(GLenum eMode);
		bool define(void* tg = 0);
		virtual void SaveObject(QTextStream& out);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf, unsigned int fdtype);
		virtual void hertzian_contact_force(void* p, void* v, void* w, void* f, void* m, float ma, float dt, parview::contactConstant* cc){}
		void SetDataFromFile(QTextStream& in);
		void insert_particle_buffer(float* p, float* v, float* f, float* m, unsigned int n, unsigned int part);
		void alloc_buffer(QFile& pf, unsigned int n);
		void alloc_buffer_sph(QFile& pf, unsigned int n);
		void alloc_buffer_dem(QFile& pf, unsigned int n);
		void SetFromFile(QFile& pf, unsigned int _np = 0);
		
		float* getPosition(unsigned int id) { return pos[id]; }
		float* getVelocity(unsigned int id) { return vel[id]; }
		QString& Name() { return name; }
		unsigned int Np() { return np;  }
		float GetMaxRadius() { return maxRadius; }
		void bindingWindowHeight(int *height) { winHeight = height; }
		template<typename base_type>
		algebra::vector4<base_type> getPositionToV4(unsigned int id)
		{
			unsigned int cf = view_controller::getFrame();
			float* outPos = pos[cf];
			return algebra::vector4<base_type>(
				static_cast<base_type>(outPos[id * 4 + 0]),
				static_cast<base_type>(outPos[id * 4 + 1]),
				static_cast<base_type>(outPos[id * 4 + 2]),
				static_cast<base_type>(outPos[id * 4 + 3])
				);
		}
		template<typename base_type>
		algebra::vector4<base_type> getVelocityToV4(unsigned int id)
		{
			unsigned int cf = view_controller::getFrame();
			float* outVel = vel[cf];
			return algebra::vector4<base_type>(
				static_cast<base_type>(outVel[id * 4 + 0]),
				static_cast<base_type>(outVel[id * 4 + 1]),
				static_cast<base_type>(outVel[id * 4 + 2]),
				static_cast<base_type>(outVel[id * 4 + 3])
				);
		}
		double getPressure(unsigned id);
		double getFreeSurfaceValue(unsigned int id);
		bool isFreeSurface(unsigned int id);
		void changeParticleColor(unsigned int id);
		void drawSupportSphere(unsigned int id);
		void AddParticlesFromFile(QFile& pf);
		void AddParticleFromManual(float* p, float* v);
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
		float maxRadius;
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
		bool isglewinit;
// 		// Qt
		QWidget *byGeoTab;
		QWidget *byManualTab;
		QTabWidget *tabWidget;
		QDialog *particleDialog;
		QComboBox *CBGeometry;
		QLineEdit *LEMRadius;
		QLineEdit *LEName;
		QLineEdit *LERadius;
		QLineEdit *LEPosition;
		QLineEdit *LEVelocity;
		QGridLayout *particleLayout;
		QStringList geoComboxList;
		QStringList cpProcess;
		
		private slots:
		virtual void Click_ok();
		virtual void Click_cancel();

	signals:
		void mySignal();
	};
}

#endif