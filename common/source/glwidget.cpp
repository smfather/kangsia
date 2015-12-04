#include "glwidget.h"
#include <QDebug>
/*#include <QKeyEvent>*/
#include <QMouseEvent>
#include <QTimer>

#include <math.h>
#include "types.h"
#include "gl/freeglut.h"

#include "view_line.h"
#include "view_cube.h"
#include "view_plane.h"
#include "view_particles.h"
#include "view_shape.h"
#include "view_mass.h"
#include "view_rectangle.h"
#include "view_object.h"
#include "view_bondData.h"

#include "view_controller.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define METER 1000

using namespace parview;

GLuint makeCubeObject(int* index, float* vertex)
{
	GLuint list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glShadeModel(GL_SMOOTH);
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glBegin(GL_QUADS);
	for (int i(0); i < 6; i++){
		int *id = &index[i * 4];
		glVertex3f(vertex[id[3] * 3 + 0], vertex[id[3] * 3 + 1], vertex[id[3] * 3 + 2]);
		glVertex3f(vertex[id[2] * 3 + 0], vertex[id[2] * 3 + 1], vertex[id[2] * 3 + 2]);
		glVertex3f(vertex[id[1] * 3 + 0], vertex[id[1] * 3 + 1], vertex[id[1] * 3 + 2]);
		glVertex3f(vertex[id[0] * 3 + 0], vertex[id[0] * 3 + 1], vertex[id[0] * 3 + 2]);
	}
	glEnd();
	glEndList();
	return list;
}

GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 10.0f, 10.0f, -10.0f, 1.0f };
GLfloat LightPosition2[] = { 10.0f, 10.0f, 10.0f, 1.0f };

GLWidget::GLWidget(/*document* _Doc,*/ QWidget *parent)
	: QGLWidget(parent)
	//, Doc(_Doc)
{
	
	viewOption = 0;
	xRot = 0;
	yRot = 0;
	zRot = 0;
	unit = 1;
	zoom = -1.0;
	//zoom = -6.16199875;
	trans_x = 0;
	moveScale = 0.01f;
	trans_y = 0;
	IconScale = 0.1;
	isSetParticle = false;
	//particle_ptr = NULL;
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
	timer->start(1);
	for (int i = 0; i < 256; i++)
	{
		keyID[i] = false;
		selected[i] = false;
	}
	LBOTTON = false;
	onZoom = false;
	onRotation = false;
	isAnimation = false;
	aFrame = 0;
	for (int i(0); i < 256; i++){
		polygons[i] = 0; \
	}
	numPolygons = 0;

	votype = ALL_DISPLAY;
	// 	myCgContext = 0;
	// 	//myCgPSFragmentProfile = CG_PROFILE_UNKNOWN;
	// 	myCgPSFragmentProgram = 0;
	// 	//myCgPSVertexProfile = CG_PROFILE_UNKNOWN;
	// 	myCgPSVertexProgram = 0;
}

GLWidget::~GLWidget()
{
	makeCurrent();
	glDeleteLists(coordinate, 1);
	for (std::map<QString, parview::Object*>::iterator obj = objs.begin(); obj != objs.end(); obj++){
		delete obj->second;
	}
	// 	if(myCgPSVertexProgram) cgDestroyProgram(myCgPSVertexProgram); myCgPSVertexProgram = 0;
	// 	if(myCgPSFragmentProgram) cgDestroyProgram(myCgPSFragmentProgram); myCgPSFragmentProgram = 0;
	// 	if(myCgContext) cgDestroyContext(myCgContext); myCgContext = 0;
}

void GLWidget::setXRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setYRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setZRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::ShowContextMenu(const QPoint& pos)
{
	QPoint globalPos = this->mapToGlobal(pos);
	QMenu myMenu;
	/*for (std::list<QString>::iterator str = stringList.begin(); str != stringList.end(); str++){
		QString qstr = *str;
		myMenu.addAction(qstr);
		myMenu.addAction("  Hide");
	}*/
	//myMenu.addAction("Menu Item 1");

	QAction *selectedItem = myMenu.exec(globalPos);
}

// void GLWidget::checkForCgError(const char *situation)
// {
// 	CGerror error;
// 	const char *string = cgGetLastErrorString(&error);
// 
// 	if (error != CG_NO_ERROR) {
// // 		printf("%s: %s: %s\n",
// // 			myProgramName, situation, string);
// 		if (error == CG_COMPILER_ERROR) {
// 			std::cout << cgGetLastListing(myCgContext) << std::endl;
// 		}
// 		exit(1);
// 	}
// }

void GLWidget::onParticleSystem()
{
	// 	glPointSize(6.0f);
	// 		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 		glEnable(GL_POINT_SMOOTH);
	// 		glEnable(GL_BLEND);
	// 	
	// 		myCgContext = cgCreateContext();
	// 		checkForCgError("creating context");
	// 		cgGLSetDebugMode(CG_FALSE);
	// 		cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);
	// 	
	// 		myCgPSVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
	// 		cgGLSetOptimalOptions(myCgPSVertexProfile);
	// 		checkForCgError("selecting vertex profile");
	// 		myCgPSVertexProgram = 
	// 			cgCreateProgramFromFile(
	// 				myCgContext,
	// 				CG_SOURCE,
	// 				myPSVertexProgramFileName,
	// 				myCgPSVertexProfile,
	// 				myPSVertexProgramName,
	// 				NULL);
	// 		checkForCgError("creating vertex program from file");
	// 		cgGLLoadProgram(myCgPSVertexProgram);
	// 		checkForCgError("loading vertex program");
	// 	
	// 		myCgVertexParam_pointScale =
	// 			cgGetNamedParameter(myCgPSVertexProgram, "pointScale");
	// 		checkForCgError("could not get pointScale parameter");
	// 		
	// 		myCgVertexParam_pointSize =
	// 			cgGetNamedParameter(myCgPSVertexProgram, "pointRadius");
	// 		checkForCgError("could not get pointSize parameter");
	// 	
	// 		myCgVertexParam_modelView = 
	// 			cgGetNamedParameter(myCgPSVertexProgram, "modelView");
	// 		checkForCgError("could not get modelView parameter");
	// 		myCgVertexParam_modelViewProj =
	// 			cgGetNamedParameter(myCgPSVertexProgram, "modelViewProj");
	// 		checkForCgError("could not get modelViewPorj parameter");
	// 	
	// 		myCgPSFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	// 		cgGLSetOptimalOptions(myCgPSFragmentProfile);
	// 		checkForCgError("selecting fragment profile");
	// 	
	// 		myCgPSFragmentProgram = 
	// 			cgCreateProgramFromFile(
	// 			myCgContext,
	// 			CG_SOURCE,
	// 			myPSFragmentProgramFileName,
	// 			myCgPSFragmentProfile,
	// 			myPSFragmentProgramName,
	// 			NULL);
	// 		checkForCgError("creating fragment program from file");
	// 		cgGLLoadProgram(myCgPSFragmentProgram);
	// 		checkForCgError("loading fragment program");
}

void GLWidget::initializeGL()
{
	// 	static const GLfloat lightPos[4] = { 5.0f, 5.0f, 10.0f, 1.0f };
	// 	static const GLfloat reflectance1[4] = { 0.8f, 0.1f, 0.0f, 1.0f };
	// 	static const GLfloat reflectance2[4] = { 0.0f, 0.8f, 0.2f, 1.0f };
	// 	static const GLfloat reflectance3[4] = { 0.2f, 0.2f, 1.0f, 1.0f };

	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);


	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One

	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);	// Position The Light
	glEnable(GL_LIGHT2);								// Enable Light One

	coordinate = makeCoordinate();

	glEnable(GL_NORMALIZE);

	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearColor(103.0f / 255.0f, 153.0f / 255.0f, 255.0f / 255.0f, 1.0);
}



GLuint GLWidget::makePolygonObject(double* points, double* normals, int* indice, int size)
{
	GLuint list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glShadeModel(GL_SMOOTH);
	glColor3f(0.0f, 0.0f, 1.0f);
	for (int i(0); i < size; i++){
		glBegin(GL_TRIANGLES);
		{
			glNormal3dv(&normals[i * 3]);
			glVertex3dv(&points[indice[i * 3 + 0] * 3]);
			glVertex3dv(&points[indice[i * 3 + 1] * 3]);
			glVertex3dv(&points[indice[i * 3 + 2] * 3]);
		}
		glEnd();
	}
	glEndList();
	polygons[numPolygons] = list;
	numPolygons++;
	return list;
}

int GLWidget::selection(int x, int y)
{
	//GLuint buffer[512];
	//GLint hits;
	//GLint viewport[4];
	//stringList.clear();
	//glGetIntegerv(GL_VIEWPORT, viewport);
	//glSelectBuffer(512, buffer);
	//(void)glRenderMode(GL_SELECT);
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 1.0f, 1.0f, viewport);
	//gluPerspective(60.0, ratio, 0.1f, 1000.0f);
	//paintGL();
	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//hits = glRenderMode(GL_RENDER);
	choose = 0;
	//int depth = -1;
	//if (hits > 0){
	//	choose = buffer[3];
	//	depth = buffer[1];
	//	for (int loop = 1; loop < hits; loop++){
	//		if (buffer[loop * 4 + 1] < GLuint(depth)){
	//			choose = buffer[loop * 4 + 3];
	//			depth = buffer[loop * 4 + 1];
	//		}
	//	}

	//	stringList.push_back(objects->getSelectObjectName(choose));
	//	if (!selected[choose]){
	//		selected[choose] = true;
	//	}
	//	else{
	//		selected[choose] = false;
	//	}
	//}
	//else{
	//	for (int i = 0; i < 256; i++){
	//		selected[i] = false;
	//	}
	//}
	////	objects->sphData->setSelectElement(choose);
	////	selected[choose] = true;
	return choose;
}

GLuint GLWidget::makeCoordinate()
{
	GLuint list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glShadeModel(GL_FLAT);

	qglColor(QColor(255, 0, 0));
	glBegin(GL_LINES);
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(IconScale*1.0f, 0.0f, 0.0f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(IconScale*1.5f, 0.0f, 0.0f);
		float angInc = (float)(45 * (M_PI / 180));
		for (int i = 0; i < 9; i++)
		{
			float rad = angInc * i;
			glVertex3f(IconScale*1.0f, cos(rad)*IconScale*0.15f, sin(rad)*IconScale*0.15f);
		}
	}
	glEnd();
	glBegin(GL_LINES);
	{
		glVertex3f(IconScale*1.5f, IconScale*(-0.1f), 0.0f);
		glVertex3f(IconScale*1.3f, IconScale*(-0.3f), 0.0f);
		glVertex3f(IconScale*1.3f, IconScale*(-0.1f), 0.0f);
		glVertex3f(IconScale*1.5f, IconScale*(-0.3f), 0.0f);
	}
	glEnd();

	qglColor(QColor(0, 255, 0));
	glBegin(GL_LINES);
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, IconScale*1.0f, 0.0f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(0.0f, IconScale*1.5f, 0.0f);
		float angInc = (float)(45 * (M_PI / 180));
		for (int i = 0; i < 9; i++)
		{
			float rad = angInc * i;
			glVertex3f(cos(rad)*IconScale*0.15f, IconScale*1.0f, sin(rad)*IconScale*0.15f);
		}
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glVertex3f(IconScale*(-0.1f), IconScale*1.5f, 0.0f);
		glVertex3f(IconScale*(-0.2f), IconScale*1.4f, 0.0f);
		glVertex3f(IconScale*(-0.3f), IconScale*1.5f, 0.0f);
		glVertex3f(IconScale*(-0.2f), IconScale*1.4f, 0.0f);
		glVertex3f(IconScale*(-0.2f), IconScale*1.4f, 0.0f);
		glVertex3f(IconScale*(-0.2f), IconScale*1.25f, 0.0f);
	}
	glEnd();

	qglColor(QColor(0, 0, 255));
	glBegin(GL_LINES);
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, IconScale*1.0f);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(0.0f, 0.0f, IconScale*1.5f);
		float angInc = (float)(45 * (M_PI / 180));
		for (int i = 0; i < 9; i++)
		{
			float rad = angInc * i;
			glVertex3f(cos(rad)*IconScale*0.15f, sin(rad)*IconScale*0.15f, IconScale*1.0f);
		}
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glVertex3f(IconScale*(-0.3f), 0.0f, IconScale*1.5f);
		glVertex3f(IconScale*(-0.1f), 0.0f, IconScale*1.5f);
		glVertex3f(IconScale*(-0.1f), 0.0f, IconScale*1.5f);
		glVertex3f(IconScale*(-0.3f), IconScale*(-0.2f), IconScale*1.5f);
		glVertex3f(IconScale*(-0.3f), IconScale*(-0.2f), IconScale*1.5f);
		glVertex3f(IconScale*(-0.1f), IconScale*(-0.2f), IconScale*1.5f);
	}
	glEnd();

	glEndList();
	return list;
}

void GLWidget::DrawCartesianCoordinates(vector3<double>& pos, vector3<double>& angle)
{
	glDisable(GL_LIGHTING);
	glTranslated(unit*pos.x, unit*pos.y, unit*pos.z);
	glRotated(angle.x / 16, 1.0, 0.0, 0.0);
	glRotated(angle.y / 16, 0.0, 1.0, 0.0);
	glRotated(angle.z / 16, 0.0, 0.0, 1.0);
	glCallList(coordinate);
	glEnable(GL_LIGHTING);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DrawCartesianCoordinates(vector3<double>(-0.9, -0.9f, 0.0f), vector3<double>(xRot, yRot, zRot));
	glPopMatrix();

	resizeGL(wWidth, wHeight/*, -trans_x, -trans_y*/);
	glTranslatef(0.0f, 0.0f, zoom);
	glTranslatef(trans_x, trans_y, 0.0f);
	glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);

	for (std::map<QString, parview::Object*>::iterator obj = objs.begin(); obj != objs.end(); obj++){
		if (viewOption == 2 && obj->second->Type() != NO_GEOMETRY_TYPE)
			continue;
		obj->second->draw();
	}

	/*glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
	glTranslatef(2 * trans_x, 2 * trans_y, 0.0f);*/
	

	if (view_controller::Play()){
		view_controller::move2forward1x();
		if (isRtOpenFile)
			UpdateRtDEMData();
	}

	

	glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::resizeGL(int width, int height)
{
	wWidth = width; wHeight = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ratio = (GLfloat)(width) / (GLfloat)(height);
	/*if (width <= height){
		glOrtho(-100.0, 100.0, -100 / ratio, 100.0 / ratio, 1.0, -1.0);
	}
	else{
		glOrtho(-100.0*ratio, 100.0*ratio, -100.0, 100.0, 1.0, -1.0);
	}*/
	gluPerspective(60.0f, ratio, 0.01f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//if (tx == 0.0f && ty == 0.0f)
		glTranslated(trans_x, trans_y, zoom);
	//else
		//glTranslated(tx, ty, zoom);
}

void GLWidget::wheelEvent(QWheelEvent *e)
{
	QPoint  p = e->angleDelta();
	float pzoom = zoom;
	p.y() > 0 ? zoom -= 2.f*moveScale : zoom += 2.f*moveScale;
	// 	if(zoom <= 0){
	// 		zoom = 0.05f;
	// 	}
	///paintGL();
	//e->accept();
	setFocusPolicy(Qt::StrongFocus);
	// 	ev->buttons() = Qt::LeftButton;
	// 	mousePressEvent(ev);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	// 	if(event->type() == QEvent::None) 
	// 		return;
	lastPos = event->pos();
	if (event->button() == Qt::RightButton){
		//selection(lastPos.x(), lastPos.y());
	}
	if (event->button() == Qt::MiddleButton){
		onZoom = true;
	}
	if (!keyID[90] && !keyID[84] && !keyID[82]){
		if (event->button() == Qt::LeftButton){
			//int choose = selection(lastPos.x(), lastPos.y());

			onRotation = true;
		}
	}
	// 	lastPos = event->pos();
	// 	if(event->button() == Qt::RightButton){
	// 		//selection(lastPos.x(), lastPos.y());
	// 	}
	// 	if(!keyID[90] && !keyID[84] && !keyID[82]){
	// 		if(event->button() == Qt::LeftButton){
	// 			//int choose = selection(lastPos.x(), lastPos.y());
	// 
	// 		}
	// 	}
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (onRotation)
		onRotation = false;

	if (onZoom)
		onZoom = false;

	if (event->button() == Qt::LeftButton){
		if (keyID[90])
			keyID[90] = false;
		if (keyID[84])
			keyID[84] = false;
		if (keyID[82])
			keyID[82] = false;
		//selection(lastPos.x(), lastPos.y());
		//viewSystem::keyPressed = false;
	}
	// 	if(event->button() == Qt::LeftButton){
	// 		if(keyID[90]) 
	// 			keyID[90] = false;
	// 		if(keyID[84])
	// 			keyID[84] = false;
	// 		if(keyID[82])
	// 			keyID[82] = false;
	// 		//selection(lastPos.x(), lastPos.y());
	// 		//viewSystem::keyPressed = false;
	// 	}
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (keyID[84]){
		dy > 0 ? trans_y -= 0.1f*moveScale*dy : trans_y -= 0.1f*moveScale*dy;
		dx > 0 ? trans_x += 0.1f*moveScale*dx : trans_x += 0.1f*moveScale*dx;
	}
	if (!keyID[84] && onRotation) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
		// 		xRot += dy * 0.2f;
		// 		yRot += dx * 0.2f;
	}
	if (onZoom)
	{
		dy > 0 ? zoom -= 0.1f*moveScale : zoom += 0.1f*moveScale;
		// 		dy > 0 ? zoom += 5.f*moveScale : zoom -= 5.f*moveScale;
		// 		if(zoom <= 0){
		// 			zoom = 0.05f;
		// 		}
	}
	lastPos = event->pos();
	// 	int dx = event->x() - lastPos.x();
	// 	int dy = event->y() - lastPos.y();
	// 
	// 	if (event->buttons() & Qt::LeftButton) {
	// 		if(keyID[90]){
	// 			dy > 0 ? zoom -= 0.05 : zoom += 0.05;
	// 			updateGL();
	// 		}
	// 		else if(keyID[82]){
	// 			setXRotation(xRot + 8 * dy); 
	// 			setYRotation(yRot + 8 * dx);
	// 		}
	// 		else if(keyID[84]){
	//  			dy > 0 ? trans_y -= 0.005*dy : trans_y -= 0.005*dy;
	//  			dx > 0 ? trans_x += 0.005*dx : trans_x += 0.005*dx;
	// 		}
	// 	} else if (event->buttons() & Qt::RightButton) {
	// 		setXRotation(xRot + 8 * dy);
	// 		setZRotation(zRot + 8 * dx);
	// 	}
	// 	lastPos = event->pos();
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
	switch (e->key()){
	case Qt::Key_Up:
		verticalMovement() += 0.1f*moveScale;
		break;
	case Qt::Key_Down:
		verticalMovement() -= 0.1f*moveScale;
		break;
	case Qt::Key_Left:
		horizontalMovement() -= 0.1f*moveScale;
		break;
	case Qt::Key_Right:
		horizontalMovement() += 0.1f*moveScale;
		break;
	case Qt::Key_Plus:
		moveScale += 0.001f;
		break;
	case Qt::Key_Minus:
		moveScale -= 0.001f;
		break;
	case 90:
		setKeyState(true, 90);
		break;
	case 84:
		setKeyState(true, 84);
		break;
	case 82:
		setKeyState(true, 82);
		break;
		// 	case 46:
		// 		glWidget->NextAnimationPart();
		// 		break;
		// 	case 44:
		// 		glWidget->PriviousAnimationPart();
		// 		break;
	}
	if (moveScale <= 0){
		moveScale = 0.0f;
	}
}

void GLWidget::normalizeAngle(int *angle)
{
	while (*angle < 0)
		*angle += 360 * 16;
	while (*angle > 360 * 16)
		*angle -= 360 * 16;
}

void GLWidget::getDemFileData(QStringList& fnames, bool rt)
{
	isRtOpenFile = rt;
	outputNameList = fnames;
	unsigned int fdtype = 0;
	int type = -2;
	parview::particles* par = NULL;
	for (QList<QString>::iterator it = fnames.begin(); it != fnames.end(); it++){
		int begin = it->lastIndexOf("/");
		int end = it->length();
		std::string fname = it->toStdString().substr(begin + 1, end - 1);
		if (fname == "boundary.bin"){
			QFile pf(*it);
			pf.open(QIODevice::ReadOnly);
			pf.read((char*)&fdtype, sizeof(unsigned int));
			while (1){
				pf.read((char*)&type, sizeof(int));
				if (type == INT_MIN)
					break;
				switch (type)
				{
				case LINE:
				{
					parview::line* line = new parview::line;
					line->setLineData(pf);
					line->define();
					objs[line->Name()] = line;
				}
				break;
				case RECTANGLE:
				{
					parview::rectangle* rect = new parview::rectangle;
					rect->setRectangleData(pf, fdtype);
					rect->define();
					objs[rect->Name()] = rect;
					break;
				}
				case CUBE:
				{
					QString name;
					char nm[256] = { 0, };
					int name_size = 0;
					pf.read((char*)&name_size, sizeof(int));
					pf.read((char*)nm, sizeof(char)*name_size);
					name.sprintf("%s", nm);
					parview::cube* c = new parview::cube;
					c->setType(CUBE);
					c->setName(name);
					save_cube_info sci;
					double vertice[24] = { 0, };
					pf.read((char*)&sci, sizeof(save_cube_info));
					c->origin[0] = (float)sci.px; c->origin[1] = (float)sci.py; c->origin[2] = (float)sci.pz;
					c->width = (float)sci.sx; c->height = (float)sci.sy; c->depth = (float)sci.sz;
					pf.read((char*)vertice, sizeof(double) * 3 * 8);
					for (int i = 0; i < 24; i++){
						c->vertice[i] = (float)vertice[i];
					}
					c->define();
					objs[name] = c;
				}
				break;
				case SHAPE:
				{
					parview::shape* sh = new parview::shape;

					sh->setShapeData(pf);

					sh->define();
					objs[sh->Name()] = sh;
				}
				break;
				case OBJECT:
				{
					parview::object* obj = new parview::object;
					obj->setObjectData(pf);
					obj->define();
					objs[obj->Name()] = obj;
				}
				break;
				case MASS:
				{
					QString name;
					int name_size = 0;
					char nm[256] = { 0, };
					pf.read((char*)&name_size, sizeof(int));
					pf.read((char*)nm, sizeof(char)*name_size);
					name.sprintf("%s", nm);
					std::map<QString, Object*>::iterator obj = objs.find(name);
					if (obj != objs.end()){
						//parview::mass *m = obj->second->Mass_ptr();
						if (!obj->second->Mass_ptr())
							obj->second->allocMass();

						obj->second->Mass_ptr()->setMassData(pf);
					}
				}
				break;
				}
			}
			pf.close();
		}
		else{
			if(!par)
				par = new parview::particles;
			QFile pf(*it);
			pf.open(QIODevice::ReadOnly);
			pf.read((char*)&fdtype, sizeof(unsigned int));
			par->alloc_buffer_dem(pf, fdtype);
			pf.read((char*)&type, sizeof(int));
			if (type == MASS){
				QString name;
				int name_size = 0;
				char nm[256] = { 0, };
				pf.read((char*)&name_size, sizeof(int));
				pf.read((char*)nm, sizeof(char)*name_size);
				name.sprintf("%s", nm);
				std::map<QString, Object*>::iterator obj = objs.find(name);
				if (obj != objs.end()){
					//parview::mass *m = obj->second->Mass_ptr();
					if (!obj->second->Mass_ptr())
						obj->second->allocMass();

					obj->second->Mass_ptr()->setMassData(pf);
				}
			}
			/*if (type == OBJECT){
				QString name;
				int name_size = 0;
				char nm[256] = { 0, };
				pf.read((char*)&name_size, sizeof(int));
				pf.read((char*)nm, sizeof(char)*name_size);
				name.sprintf("%s", nm);
				std::map<QString, Object*>::iterator obj = objs.find(name);
				if (obj != objs.end()){
					obj->AppendPosition(pf);
				}
			}*/
			pf.close();
			if (rt){
				view_controller::setTotalFrame(fnames.size() - 1);
				break;
			}
			else{
				view_controller::upBufferCount();
			}			
		}
	}
	if (par && !isSetParticle){
		par->bindingWindowHeight(&wHeight);
		par->define();
		objs["particles"] = par;
		isSetParticle = true;
		pview_ptr = par;
	}	
}

void GLWidget::getSphFileData(QStringList& fnames)
{
	bool b_pos = false;
	bool b_press = false;
	bool b_vel = false;
	for (QList<QString>::iterator it = fnames.begin(); it != fnames.end(); it++)
	{
		int begin = it->lastIndexOf("/");
		int end = it->length();
		std::string fname = it->toStdString().substr(begin + 1, end - 1);
		if (fname == "check.bin"){
			char v;
			QFile pf(*it);
			pf.open(QIODevice::ReadOnly);
			pf.read(&v, sizeof(char));
			pf.read(&v, sizeof(char));
			if (v == 'o')
				b_pos = true;
			pf.read(&v, sizeof(char));
			if (v == 'r')
				b_press = true;
			pf.read(&v, sizeof(char));
			if (v == 'e')
				b_vel = true;
			pf.close();
		}
	}
	parview::particles* par = new parview::particles;
	for (QList<QString>::iterator it = fnames.begin(); it != fnames.end(); it++){
		QFile pf(*it);
		pf.open(QIODevice::ReadOnly);
		par->alloc_buffer_sph(pf, 0);
		pf.close();
		view_controller::upBufferCount();
	}
	par->bindingWindowHeight(&wHeight);
	par->define();
	objs["particles"] = par;
	isSetParticle = true;
	pview_ptr = par;
}

void GLWidget::getFileData(QFile& pf)
{
	
	//int state = 0;
	float isClose = 0.0f;
	bool isStartOneStep = false;
	unsigned int noCount = 0;
	parview::particles* par = NULL;
	int type = -2;
	output_info oi;
	unsigned int tframe = 0;
	double time = 0;
	QString name;
	pf.read((char*)&oi, sizeof(output_info));
	while (1){		
		pf.read((char*)&type, sizeof(int));
		if (noCount > 1000)
			type = -1;
		switch (type){
		case INT_MIN:
			pf.read((char*)&time, sizeof(double));
			times[view_controller::getTotalBuffers()] = static_cast<float>(time);
			isStartOneStep = true;
			break;
		case INT_MAX:
			if (isStartOneStep){
				isStartOneStep = false;
			}
			else{
				noCount++;
				break;
			}
			view_controller::upBufferCount();
			break;
		case CLOSE_SAVE:
			if (par){
				par->bindingWindowHeight(&wHeight);
				par->define();
				objs["particles"] = par;
				isSetParticle = true;
				pview_ptr = par;
			}
			return;
	
		case PLANE:
			{
				parview::plane *p = new parview::plane;
				pf.read((char*)&p->info_plane(), sizeof(save_plane_info));
				p->define();
			}
			break;
		case CUBE:
			{
				char nm[256] = { 0, };
				int name_size = 0;
				pf.read((char*)&name_size, sizeof(int));
				pf.read((char*)nm, sizeof(char)*name_size);
				name.sprintf("%s", nm);
				parview::cube* c = new parview::cube;
				c->setType(CUBE);
				c->setName(name);
				save_cube_info sci;
				double vertice[24] = { 0, };
				pf.read((char*)&sci, sizeof(save_cube_info));
				c->origin[0] = (float)sci.px; c->origin[1] = (float)sci.py; c->origin[2] = (float)sci.pz;
				c->width = (float)sci.sx; c->height = (float)sci.sy; c->depth = (float)sci.sz;
				pf.read((char*)vertice, sizeof(double) * 3 * 8);
				for (int i = 0; i < 24; i++){
					c->vertice[i] = (float)vertice[i];
				}
				c->define();
				objs[name] = c;
			}
			break;
		case RECTANGLE:
			{
				parview::rectangle* rec = new parview::rectangle;
				rec->setRectangleData(pf, 4);

				rec->define();
				objs[rec->Name()] = rec;
			}
			break;
		case SHAPE:
			{
				parview::shape* sh = new parview::shape;
	
				sh->setShapeData(pf);

				sh->define();
				objs[sh->Name()] = sh;
			}
			break;
		case PARTICLE:
			{
				unsigned int np = 0;
				if(!par) 
					par = new parview::particles;
					
				pf.read((char*)&np, sizeof(unsigned int));
				if (np == -1)
					continue;
				par->alloc_buffer(pf, np);
			}
			break;
		case MASS:
			{
				int name_size = 0;
				char nm[256] = { 0, };
				pf.read((char*)&name_size, sizeof(int));
				pf.read((char*)nm, sizeof(char)*name_size);
				name.sprintf("%s", nm);
				std::map<QString, Object*>::iterator obj = objs.find(name);
				if (obj != objs.end()){
					//parview::mass *m = obj->second->Mass_ptr();
					if (!obj->second->Mass_ptr())
						obj->second->allocMass();

					obj->second->Mass_ptr()->setMassData(pf);
				}
			}
			break;
		default:
			
			break;
		}
		
	}
}

void GLWidget::saveCurrentData(QFile& pf)
{
	for (std::map<QString, parview::Object*>::iterator obj = objs.begin(); obj != objs.end(); obj++){		
		obj->second->saveCurrentData(pf);
	}

	int close_save = -1;
	pf.write((char*)&close_save, sizeof(int));
}

void GLWidget::UpdateRtDEMData()
{
	int type=-2;
	unsigned int target = view_controller::getFrame();

	QList<QString>::iterator it = outputNameList.begin() + 1 + target;
	int begin = it->lastIndexOf("/");
	int end = it->length();
	std::string fname = it->toStdString().substr(begin + 1, end - 1);
	QFile pf(*it);
	pf.open(QIODevice::ReadOnly);
	unsigned int fdtype;
	pf.read((char*)&fdtype, sizeof(unsigned int));
	std::map<QString, Object*>::iterator obj = objs.find("particles");
	obj->second->updateDataFromFile(pf);
	pf.read((char*)&type, sizeof(int));
	if (type == MASS){
		QString name;
		int name_size = 0;
		char nm[256] = { 0, };
		pf.read((char*)&name_size, sizeof(int));
		pf.read((char*)nm, sizeof(char)*name_size);
		name.sprintf("%s", nm);
		std::map<QString, Object*>::iterator obj = objs.find(name);
		if (obj != objs.end()){
			//parview::mass *m = obj->second->Mass_ptr();
			if (!obj->second->Mass_ptr())
				obj->second->allocMass();

			obj->second->Mass_ptr()->updateDataFromFile(pf);
		}
	}
}

void GLWidget::ChangeShapeData(QString& sname)
{
	std::map<QString, Object*>::iterator obj = objs.find("trawl");
	QFile pf(sname);
	pf.open(QIODevice::ReadOnly);
	obj->second->updateDataFromFile(pf);
}

void GLWidget::AddParticles(QString& fname)
{
	QFile pf(fname);
	pf.open(QIODevice::ReadOnly);
	std::map<QString, Object*>::iterator obj = objs.find("particles");
	particles* ps = dynamic_cast<particles*>(obj->second);
	ps->AddParticlesFromFile(pf);
	pf.close();
}

void GLWidget::AddBondData(QString& fname)
{
	parview::bondData *bd = new parview::bondData;
	
 	QFile pf(fname);
 	pf.open(QIODevice::ReadOnly);
	bd->setBondData(pf);
	pf.close();

	bd->define();

	objs["bond"] = bd;
}

void GLWidget::ChangeDisplayOption(int oid)
{
	viewOption = oid;
}

void GLWidget::ExportForceData()
{
	std::map<QString, Object*>::iterator obj = objs.find("trawl");
	QFile pf("C:/C++/result/trawl_force data/type2_angle20.txt");
	pf.open(QIODevice::WriteOnly);
	QTextStream of(&pf);
	for (unsigned int i = 0; i < view_controller::getTotalBuffers(); i++){
		vector3<float> f = obj->second->Mass_ptr()->Force(i);
		of << f.x << " " << f.y << " " << f.z << "\n";
	}
	pf.close();
}

void GLWidget::makeCube()
{
	parview::cube *c = new parview::cube;
	c->callDialog();
	c->define();
	objs[c->Name()] = c;
}

void GLWidget::makeParticle()
{
	parview::particles *p = new parview::particles;
	QStringList stList;
	std::map<QString, Object*>::iterator obj = objs.begin();
	for (; obj != objs.end(); obj++){
		stList.push_back(obj->second->Name());
	}
	p->GeometryCombeBoxWidgetList(stList);
	p->callDialog();
	p->bindingWindowHeight(&wHeight);
	obj = objs.find(p->BaseGeometryText());
	p->define(obj->second);
	objs[p->Name()] = p;
}