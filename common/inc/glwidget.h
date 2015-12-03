#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "Object.h"

#include <QGLWidget>
#include <QMenu>
#include <list>
#include <QFile>

namespace parview
{


	GLuint makeCubeObject(int* index, float* vertex);

	enum viewObjectType{
		ALL_DISPLAY,
		ONLY_FRAME,
		ONLY_PARTICLE
	};

	class GLWidget : public QGLWidget
	{
		Q_OBJECT

	public:
		GLWidget(QWidget *parent = 0);
		~GLWidget();

		void makeCube();
		void makeParticle();

		int xRotation() const { return xRot; }
		int yRotation() const { return yRot; }
		int zRotation() const { return zRot; }
		float& getZoom() { return zoom; }
		void setKeyState(bool s, int i) { keyID[i] = s; };

		void onAnimation() { isAnimation = true; }
		GLuint makePolygonObject(double* points, double* normals, int* indice, int size);
		void ExportForceData();
		//GLuint makeCubeObject(int* index, float* vertex);
		void onParticleSystem();
		//void bindingObjects(elements* obj) { objects = obj; }
		int selection(int x, int y);
		//void NextAnimationPart(int times = 1) { objects->sphData->NextAnimationPart(times); }
		//void PriviousAnimationPart(int times = 1) { objects->sphData->PriviousAnimationPart(times); }
		void setViewObject(viewObjectType viewType) { votype = viewType; };
		void getFileData(QFile& pf);
		void getSphFileData(QStringList& fnames);
		void getDemFileData(QStringList& fnames, bool rt);
		void saveCurrentData(QFile& pf);
		void UpdateRtDEMData();
		int getWindowHeight() { return wHeight; }
		bool is_set_particle() { return isSetParticle; }
		parview::Object *getParticle_ptr() { return pview_ptr;  }
		parview::Object *getViewParticle()
		{ 
			return pview_ptr;
		}

		void ChangeShapeData(QString& sname);
		void AddParticles(QString& fname);
		void AddBondData(QString& fname);
		void ChangeDisplayOption(int oid);

		public slots:
		void setXRotation(int angle);
		void setYRotation(int angle);
		void setZRotation(int angle);
		void ShowContextMenu(const QPoint& pos);

	signals:
		void xRotationChanged(int angle);
		void yRotationChanged(int angle);
		void zRotationChanged(int angle);

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void keyPressEvent(QKeyEvent *);
		void wheelEvent(QWheelEvent *);

	private:
		float& verticalMovement() { return trans_y; }
		float& horizontalMovement() { return trans_x; }
		void DrawCartesianCoordinates(vector3<double>& pos, vector3<double>& angle);
		GLuint makeCoordinate();
		//GLuint makePolygonObject(float* points, float* normals, int* indice, int size);
		void normalizeAngle(int *angle);
		//void checkForCgError(const char *situation);
		int viewOption;
		bool isRtOpenFile;
		bool isSetParticle;
		GLuint coordinate;
		GLuint polygons[256];
		int numPolygons;
		int wWidth;
		int wHeight;
		int xRot;
		int yRot;
		int zRot;
		int unit;
		float moveScale;
		float ratio;
		float zoom;
		float trans_x;
		float trans_y;

		float IconScale;

		bool onZoom;
		bool onRotation;
		bool keyID[256];
		bool selected[256];
		unsigned choose;
		bool LBOTTON;
		QPoint lastPos;
		int aFrame;
		bool isAnimation;

		float times[MAX_FRAME];

		viewObjectType votype;

		std::map<QString, parview::Object*> objs;

		parview::Object* pview_ptr = NULL;

		QStringList outputNameList;

		float maxViewPoint[3];
		float minViewPoint[3];
	};

}


#endif // GLWIDGET_H

