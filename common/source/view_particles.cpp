#include "view_particles.h"
#include "view_controller.h"
#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QComboBox>

#include "view_cube.h"

using namespace parview;

//unsigned int particles::current_frame = 0;
//unsigned int particles::buffer_count = 0;
//bool particles::is_play = false;

particles::particles()
	: Object()
	, np(0)
	, radius(0)
	, isSetColor(false)
	, name("particles")
	, isDisplaySupportRadius(false)
	, particleDialog(NULL)
{
	Object::type = NO_GEOMETRY_TYPE;
	for (int i = 0; i < MAX_FRAME; i++){
		pos[i] = NULL;
		vel[i] = NULL;
		pressure[i] = NULL;
		freeSurface[i] = NULL;
		freeSurfaceValue[i] = NULL;

		color[i] = NULL;
	}

}

particles::~particles()
{
	for (int i = 0; i < MAX_FRAME; i++){
		if (pos[i]) delete [] pos[i]; pos[i] = NULL;
		if (vel[i]) delete [] vel[i]; vel[i] = NULL;
		if (pressure[i]) delete[] pressure[i]; pressure[i] = NULL;
		if (color[i]) delete[] color[i]; color[i] = NULL;
	}
}

//bool particles::is_end_frame()
//{
//	return current_frame == buffer_count;
//}
//
//void particles::move2previous2x()
//{
//	current_frame ? (--current_frame ? --current_frame : current_frame = 0) : current_frame = 0;
//}
//
//void particles::move2previous1x()
//{
//	current_frame ? --current_frame : current_frame = 0;
//}
//
//void particles::on_play()
//{
//	is_play = true;
//}
//
//void particles::off_play()
//{
//	is_play = false;
//}
//
//void particles::move2forward1x()
//{
//	current_frame == buffer_count ? current_frame = current_frame : ++current_frame;
//}
//
//void particles::move2forward2x()
//{
//	current_frame == buffer_count ? current_frame = current_frame : (++current_frame == buffer_count ? current_frame = current_frame : ++current_frame);
//}
void particles::draw_particles()
{
	/*if (view_controller::Play())
		view_controller::move2forward1x();*/
	view_controller::is_end_frame();
	draw();
}


void particles::draw()
{
	if (isDisplaySupportRadius){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPushMatrix();
		GLUquadricObj *support;
		support = gluNewQuadric();
		glTranslatef(support_pos.x, support_pos.y, support_pos.z);
		gluSphere(support, 0.0065, 32, 32);
		glPopMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (view_controller::getRealTimeParameter()){
		buffer = pos[0];
		color_buffer = color[0];
	}
	else{
		buffer = pos[view_controller::getFrame()];
		color_buffer = color[view_controller::getFrame()];
	}
	
	glDisable(GL_LIGHTING);
	glEnable(GL_POINT_SPRITE_ARB);
	glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_NV);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	
	glUseProgram(m_program);
	glUniform1f(glGetUniformLocation(m_program, "pointScale"), (*winHeight) / tanf(60 * 0.5f*(float)PI / 180.0f));
	//glUniform1f(glGetUniformLocation(m_program, "pointRadius"), cur_radius);

	//glColor3f(1, 1, 1);
	_drawPoints();

	glUseProgram(0);
	glDisable(GL_POINT_SPRITE_ARB);
	glEnable(GL_LIGHTING);
	emit Object::mySignal();
}

void particles::_drawPoints()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (m_posVBO)
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_posVBO);
		glVertexPointer(4, GL_FLOAT, 0, 0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*np * 4, buffer);
		if (m_colorVBO)
		{
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_colorVBO);
			glColorPointer(4, GL_FLOAT, 0, 0);
			glEnableClientState(GL_COLOR_ARRAY);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*np * 4, color_buffer);
			
		}

		glDrawArrays(GL_POINTS, 0, np);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}

void particles::define(void* tg)
{
	Object *geo = (Object *)tg;

	switch (geo->Type()){
	case CUBE:
		{
			cube *c = dynamic_cast<cube*>(geo);
			algebra::vector3<unsigned int> dim3np = algebra::vector3<unsigned int>(static_cast<unsigned int>(abs(c->width / (radius * 2)))
				, static_cast<unsigned int>(abs(c->height / (radius * 2)))
				, static_cast<unsigned int>(abs(c->depth / (radius * 2))));
			if (dim3np.x == 0) dim3np.x = 1;
			if (dim3np.y == 0) dim3np.y = 1;
			if (dim3np.z == 0) dim3np.z = 1;

			bool bcond = true;
			vector3<double> p;
			float spacing = radius * 2.1f;
			/*np = dim3np.x * dim3np.y * dim3np.z;*/
			while (bcond){
				bcond = false;
				p = vector3<double>(c->minPoint[0] + radius + (dim3np.x - 1) * spacing
					, c->minPoint[1] + radius + (dim3np.y - 1) * spacing
					, c->minPoint[2] + radius + (dim3np.z - 1) * spacing);
				if (p.x + radius > c->width && dim3np.x > 1){
					dim3np.x--;
					bcond = true;
				}
				if (p.y + radius > c->height && dim3np.y > 1){
					dim3np.y--;
					bcond = true;
				}
				if (p.z + radius > c->depth && dim3np.z > 1){
					dim3np.z--;
					bcond = true;
				}
				if (!bcond)
					break;
			}
			np = dim3np.x * dim3np.y * dim3np.z;
			srand(1973);
			float jitter = radius * 0.001f;
			unsigned int p_id = 0;
			pos[view_controller::getTotalBuffers()] = new float[np * 4];
			for (unsigned int z = 0; z < dim3np.z; z++){
				for (unsigned int y = 0; y < dim3np.y; y++){
					for (unsigned int x = 0; x < dim3np.x; x++){
						//double dd = frand();
						pos[view_controller::getTotalBuffers()][p_id * 4 + 0] = (c->minPoint[0] + radius + x*spacing) + frand()*jitter;
						pos[view_controller::getTotalBuffers()][p_id * 4 + 1] = (c->minPoint[1] + radius + y*spacing) + frand()*jitter;
						pos[view_controller::getTotalBuffers()][p_id * 4 + 2] = (c->minPoint[2] + radius + z*spacing) + frand()*jitter;
						pos[view_controller::getTotalBuffers()][p_id * 4 + 3] = radius;
						p_id++;
					}
				}
			}
		}
	}
	color[view_controller::getTotalBuffers()] = new float[np * 4];
	for (unsigned int i = 0; i < np; i++){
		color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
		color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
		color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
		color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
	}

	glewInit();

	m_posVBO = 0;
	m_colorVBO = 0;
	unsigned int memSize = sizeof(float) * 4 * np;
	buffer = pos[view_controller::getFrame()];
	color_buffer = color[view_controller::getFrame()];
	if (!m_posVBO) 
		m_posVBO = createVBO(memSize, buffer);
	if (!m_colorVBO)
		m_colorVBO = createVBO(memSize, color_buffer);
	
	/*glBindBufferARB(GL_ARRAY_BUFFER, m_colorVBO);
	float *data = (float *)glMapBufferARB(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	float *ptr = data;
	float div255 = 1.0f / 255.f;
	for (unsigned int i = 0; i < np; i++){
		*ptr++ = color[0][i * 4 + 0];
		*ptr++ = color[0][i * 4 + 1];
		*ptr++ = color[0][i * 4 + 2];
		*ptr++ = color[0][i * 4 + 3];*/
		//algebra::vector4<float> v = algebra::vector4<float>(0.0f, 0.0f, 0.0f, 0.0f/*vel[i*4+0], vel[i*4+1], vel[i*4+2], vel[i*4+3]*/);
		//float mag_vel = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		//if (i == 12){
		//	*ptr++ = 1.0f;
		//	*ptr++ = 0.0f;
		//	*ptr++ = 0.0f;
		//	*ptr++ = 1.0f;
		//	continue;
		//}
		//if (mag_vel > 1){
		//	*ptr++ = 1.0f;
		//	*ptr++ = 0.0f;
		//	*ptr++ = 0.0f;
		//}
		//else{
		//	*ptr++ = mag_vel;
		//	*ptr++ = 0.0f;
		//	*ptr++ = 1.0f - mag_vel;
		//}
		////ptr+=3;
		//*ptr++ = 1.0f;
	//}
	//glUnmapBufferARB(GL_ARRAY_BUFFER);

	m_program = _compileProgram(vertexShader, spherePixelShader);
}

unsigned int particles::createVBO(unsigned int size, float *bufferData)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, bufferData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

unsigned int particles::_compileProgram(const char *vsource, const char *fsource)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vsource, 0);
	glShaderSource(fragmentShader, 1, &fsource, 0);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	// check if program linked
	GLint success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		char temp[256];
		glGetProgramInfoLog(program, 256, 0, temp);
		printf("Failed to link program:\n%s\n", temp);
		glDeleteProgram(program);
		program = 0;
	}

	return program;
}

void particles::updateDataFromFile(QFile& pf)
{
	double time = 0;
	double radius = 0;
	double _pos[3] = { 0, };
	double _vel[3] = { 0, };
	color_type clr;
	int vecSize = 0;
	
	pf.read((char*)&vecSize, sizeof(int));
	pf.read((char*)&time, sizeof(double));
	pf.read((char*)&np, sizeof(unsigned int));
	bool *isShapeContact = new bool[np];
	if (vecSize == 4){
		pf.read((char*)&clr, sizeof(int));
		pf.read((char*)&radius, sizeof(double));

		//QString fname;
		//fname.sprintf("E:/dem/type1_angle30/part%04d.bin", view_controller::getFrame());
		//QFile of(fname);
		//of.open(QIODevice::WriteOnly);

		double *tmp = new double[np * vecSize];
		pf.read((char*)tmp, sizeof(double) * np * vecSize);

		//of.write((char*)tmp, sizeof(double) * np * vecSize);

		for (unsigned int i = 0; i < np * vecSize; i++){
			pos[0][i] = (float)tmp[i];
		}
		pf.read((char*)tmp, sizeof(double) * np * vecSize);

		//of.write((char*)tmp, sizeof(double) * np * vecSize);

		for (unsigned int i = 0; i < np * vecSize; i++){
			vel[0][i] = (float)tmp[i];
		}
		pf.read((char*)isShapeContact, sizeof(bool)*np);
		delete[] tmp;
		for (unsigned int i = 0; i < np; i++){
			if (isShapeContact[i]){
				color[0][i * 4 + 0] = 0.0;
				color[0][i * 4 + 1] = 1.0;
				color[0][i * 4 + 2] = 0.0;
				color[0][i * 4 + 3] = 1.0;
			}
		}
		delete[] isShapeContact;
		return;
	}
	for (unsigned int i = 0; i < np; i++){
		pf.read((char*)&clr, sizeof(int));
		pf.read((char*)&radius, sizeof(double));
		pf.read((char*)_pos, sizeof(double) * vecSize);
		pf.read((char*)_vel, sizeof(double) * vecSize);
		pos[0][i * 4 + 0] = (float)_pos[0];
		pos[0][i * 4 + 1] = (float)_pos[1];
		pos[0][i * 4 + 2] = (float)_pos[2];
		pos[0][i * 4 + 3] = radius == 0.0 ? (float)_pos[3] : radius;

		vel[0][i * vecSize + 0] = (float)_vel[0];
		vel[0][i * vecSize + 0] = (float)_vel[1];
		vel[0][i * vecSize + 0] = (float)_vel[2];
	}
	
}

void particles::alloc_buffer_dem(QFile& pf, unsigned int fdtype)
{
	if (fdtype == 4){
		float time = 0;
		pf.read((char*)&time, sizeof(float));
		pf.read((char*)&np, sizeof(unsigned int));
		pos[view_controller::getTotalBuffers()] = new float[np * 4];
		vel[view_controller::getTotalBuffers()] = new float[np * 4];
		color[view_controller::getTotalBuffers()] = new float[np * 4];
		pf.read((char*)pos[view_controller::getTotalBuffers()], sizeof(float)*np * 4);
		pf.read((char*)vel[view_controller::getTotalBuffers()], sizeof(float)*np * 4);
		float radius = pos[view_controller::getTotalBuffers()][3];
		for (unsigned int i = 0; i < np; i++){
			color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
		}
	}
	else{
		double time = 0;
		double radius = 0;
		double _pos[3] = { 0, };
		double _vel[3] = { 0, };
		color_type clr;
		int vecSize = 0;
		bool *isShapeContact = NULL;
		pf.read((char*)&vecSize, sizeof(int));
		pf.read((char*)&time, sizeof(double));
		pf.read((char*)&np, sizeof(unsigned int));
		pos[view_controller::getTotalBuffers()] = new float[np * 4];
		vel[view_controller::getTotalBuffers()] = new float[np * vecSize];
		color[view_controller::getTotalBuffers()] = new float[np * 4];
		isShapeContact = new bool[np];
		if(vecSize == 4){
			pf.read((char*)&clr, sizeof(int));
			pf.read((char*)&radius, sizeof(double));

			double *tmp = new double[np * vecSize];
			pf.read((char*)tmp, sizeof(double) * np * vecSize);
			for (unsigned int i = 0; i < np * vecSize; i++){
				pos[view_controller::getTotalBuffers()][i] = (float)tmp[i];
			}
			pf.read((char*)tmp, sizeof(double) * np * vecSize);
			for (unsigned int i = 0; i < np * vecSize; i++){
				vel[view_controller::getTotalBuffers()][i] = (float)tmp[i];
			}
			pf.read((char*)isShapeContact, sizeof(bool)*np);
			delete[] tmp;

			for (unsigned int i = 0; i < np; i++){
				switch (clr){
				case RED:
					color[view_controller::getTotalBuffers()][i * 4 + 0] = 1.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
					break;
				case GREEN:
					color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 1] = 1.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
					break;
				case BLUE:
					color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
					break;
				}
				if (isShapeContact[i]){
					color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 1] = 1.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
				}
			}
			delete[] isShapeContact;
		}
	}
}

void particles::alloc_buffer_sph(QFile& pf, unsigned int n)
{
	char v;

	double _pos[3] = { 0, };
	double _vel[3] = { 0, };
	double _press = 0;
	double _fsval = 0;
	bool isfs;
	double time = 0.0;
	double minPressure = FLT_MAX;
	double maxPressure = FLT_MIN;
	pf.read((char*)&time, sizeof(double));
	pf.read((char*)&np, sizeof(unsigned int));
	char *ptype = new char[np];
	view_controller::addTimes(time);
	freeSurface[view_controller::getTotalBuffers()] = new bool[np];
	freeSurfaceValue[view_controller::getTotalBuffers()] = new float[np];
	pos[view_controller::getTotalBuffers()] = new float[np * 4];
	vel[view_controller::getTotalBuffers()] = new float[np * 3];
	pressure[view_controller::getTotalBuffers()] = new float[np];
	color[view_controller::getTotalBuffers()] = new float[np * 4];
	for (unsigned int i = 0; i < np; i++){
		pf.read(&v, sizeof(char));
		pf.read((char*)&isfs, sizeof(bool));
		pf.read((char*)&_fsval, sizeof(double));
		pf.read((char*)_pos, sizeof(double) * 3);
		pf.read((char*)&_press, sizeof(double));
		pf.read((char*)_vel, sizeof(double) * 3);
		freeSurface[view_controller::getTotalBuffers()][i] = isfs;
		freeSurfaceValue[view_controller::getTotalBuffers()][i] = _fsval;
		pos[view_controller::getTotalBuffers()][i * 4 + 0] = (float)_pos[0];
		pos[view_controller::getTotalBuffers()][i * 4 + 1] = (float)_pos[1];
		pos[view_controller::getTotalBuffers()][i * 4 + 2] = (float)_pos[2];
		pos[view_controller::getTotalBuffers()][i * 4 + 3] = 0.0012f;

		vel[view_controller::getTotalBuffers()][i * 3 + 0] = (float)_vel[0];
		vel[view_controller::getTotalBuffers()][i * 3 + 1] = (float)_vel[1];
		vel[view_controller::getTotalBuffers()][i * 3 + 2] = (float)_vel[2];

		pressure[view_controller::getTotalBuffers()][i] = (float)_press;
		minPressure = MIN(minPressure, _press);
		maxPressure = MAX(maxPressure, _press);
		ptype[i] = v;
	}
	//if (maxPressure < 1800){
	maxPressure = 1800;
	//}
	double grad = 180;
	double t = 0;
	double press;
	for (unsigned int i = 0; i < np; i++){
		switch (ptype[i]){
		case 'f':
			t = (pressure[view_controller::getTotalBuffers()][i] - 0) / grad;
			Object::colorRamp(t, &color[view_controller::getTotalBuffers()][i * 4]);
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
			break;
		case 'b':
			t = (pressure[view_controller::getTotalBuffers()][i] - 0) / grad;
			Object::colorRamp(t, &color[view_controller::getTotalBuffers()][i * 4]);
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
			/*color[view_controller::getTotalBuffers()][i * 4 + 0] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 1] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;*/
			break;
		case 'd':
			press = pressure[view_controller::getTotalBuffers()][i];
			t = (pressure[view_controller::getTotalBuffers()][i] - 0) / grad;
			Object::colorRamp(t, &color[view_controller::getTotalBuffers()][i * 4]);
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
			/*color[view_controller::getTotalBuffers()][i * 4 + 0] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 1] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;*/
			break;
		}
		if (ptype[i] == 'f' || ptype[i] == 'b'){
			if (freeSurface[view_controller::getTotalBuffers()][i]){
				color[view_controller::getTotalBuffers()][i * 4 + 0] = 1.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 1] = 1.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
			}
		}

	}
	delete[] ptype;
}

void particles::alloc_buffer(QFile& pf, unsigned int n)
{
	np = n;
	pos[view_controller::getTotalBuffers()] = new float[np * 4];
	vel[view_controller::getTotalBuffers()] = new float[np * 4];
	color[view_controller::getTotalBuffers()] = new float[np * 4];
	double *tmp = new double[np * 4];
	pf.read((char*)tmp, sizeof(double) * np * 4);
	for (unsigned int i = 0; i < np * 4; i++){
		pos[view_controller::getTotalBuffers()][i] = (float)tmp[i];
	}
	pf.read((char*)tmp, sizeof(double) * np * 4);
	for (unsigned int i = 0; i < np * 4; i++){
		vel[view_controller::getTotalBuffers()][i] = (float)tmp[i];
		
	}
	for (unsigned int i = 0; i < np; i++){
		if (i == 0){
			color[view_controller::getTotalBuffers()][i * 4 + 0] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 0.0f;
		}
		else{
			color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 0.0f;
		}
		
	}
	
	//view_controller::upBufferCount();
}

void particles::drawSupportSphere(unsigned int id)
{
	isDisplaySupportRadius = true;
	float *tpos = pos[view_controller::getFrame()];
	support_pos = vector3<float>(tpos[id * 4 + 0]
		, tpos[id * 4 + 1]
		, tpos[id * 4 + 2]);
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	GLUquadricObj *glSphere;
	glSphere = gluNewQuadric();*/
}

void particles::saveCurrentData(QFile& pf)
{
	
	unsigned int cf = view_controller::getFrame();
	geometry_use tp = PARTICLE;
	
	pf.write((char*)&tp, sizeof(int));
	if (view_controller::getRealTimeParameter()){
		pf.write((char*)pos[0], sizeof(float) * np * 4);
		pf.write((char*)vel[0], sizeof(float) * np * 4);
		return;
	}
	pf.write((char*)pos[cf], sizeof(float) * np * 4);
	pf.write((char*)vel[cf], sizeof(float) * np * 4);
}

algebra::vector3<float> particles::getPositionToV3(unsigned int id)
{
	unsigned int cf = view_controller::getFrame();
	float* outPos = pos[cf];
	//for (unsigned int i = 0; i < np; i++){
	//	if (outPos[i * 4 + 1] > 0.6)
	//	{
	//		bool pause = true;
	//	}
	//}
	return algebra::vector3<float>(outPos[id * 4 + 0]
								 , outPos[id * 4 + 1]
								 , outPos[id * 4 + 2]);
	
}

algebra::vector3<float> particles::getVelocityToV3(unsigned int id)
{
	unsigned int cf = view_controller::getFrame();
	float* outVel = vel[cf];
	return algebra::vector3<float>(outVel[id * 3+ 0]
		, outVel[id * 3 + 1]
		, outVel[id * 3 + 2]);
}

double particles::getPressure(unsigned id)
{
	unsigned int cf = view_controller::getFrame();
	if (!pressure[0])
		return 0.0;
	float* press = pressure[cf];
	return press[id];
}

double particles::getFreeSurfaceValue(unsigned int id)
{
	unsigned int cf = view_controller::getFrame();
	if (!freeSurfaceValue[0])
		return 0.0;
	float* fsval = freeSurfaceValue[cf];
	return fsval[id];
} 

bool particles::isFreeSurface(unsigned int id)
{
	unsigned int cf = view_controller::getFrame();
	if (!freeSurface[0])
		return 0;
	bool* fs = freeSurface[cf];
	return fs[id];
}

void particles::changeParticleColor(unsigned int id)
{
	float*  clr = color[view_controller::getFrame()];
	clr[id * 4 + 0] = 1.0f;
	clr[id * 4 + 1] = 1.0f;
	clr[id * 4 + 2] = 1.0f;
	clr[id * 4 + 3] = 1.0f;
}

void particles::AddParticlesFromFile(QFile& pf)
{
	unsigned int addnp;
	pf.read((char*)&addnp, sizeof(unsigned int));
	vector3<double> ttpos;
	float *tpos = new float[(np + addnp) * 4];
	float *tclr = new float[(np + addnp) * 4];
	memcpy(tpos, pos[view_controller::getFrame()], sizeof(float) * 4 * np);
	memcpy(tclr, color[view_controller::getFrame()], sizeof(float) * 4 * np);
	for (unsigned int i = np; i < addnp; i++){
		pf.read((char*)&ttpos, sizeof(double) * 3);
		tpos[i * 4 + 0] = (float)ttpos.x;
		tpos[i * 4 + 1] = (float)ttpos.y;
		tpos[i * 4 + 2] = (float)ttpos.z;
		tpos[i * 4 + 3] = pos[view_controller::getFrame()][4];

		tclr[i * 4 + 0] = 0.0f;
		tclr[i * 4 + 1] = 0.0f;
		tclr[i * 4 + 2] = 1.0f;
		tclr[i * 4 + 3] = 1.0f;
	}

	delete[] pos[view_controller::getFrame()];
	delete[] color[view_controller::getFrame()];

	pos[view_controller::getFrame()] = new float[(np + addnp) * 4];
	color[view_controller::getFrame()] = new float[(np + addnp) * 4];
	memcpy(pos[view_controller::getFrame()], tpos, sizeof(float)*(np + addnp)*4);
	memcpy(color[view_controller::getFrame()], tclr, sizeof(float)*(np + addnp)*4);
	np = np + addnp;
	delete[] tpos;
	delete[] tclr;


	unsigned int memSize = sizeof(float) * 4 * np;
	glDeleteBuffers(1, &m_posVBO); m_posVBO = 0;
	glDeleteBuffers(1, &m_colorVBO); m_colorVBO = 0;
	buffer = pos[view_controller::getFrame()];
	color_buffer = color[view_controller::getFrame()];
	if (!m_posVBO)
		m_posVBO = createVBO(memSize, buffer);
	if (!m_colorVBO)
		m_colorVBO = createVBO(memSize, color_buffer);
}

void particles::callDialog()
{
	if (!particleDialog){
		particleDialog = new QDialog;
		LBaseGeometry = new QLabel("Base geometry");
		CBGeometry = new QComboBox;
		LName = new QLabel("Name");
		LEName = new QLineEdit;
		LRadius = new QLabel("Radius");
		LERadius = new QLineEdit;
// 		LStartPoint = new QLabel("Start point");
// 		LEStartPoint = new QLineEdit;
// 		LEndPoint = new QLabel("End point");
// 		LEEndPoint = new QLineEdit;
		particleLayout = new QGridLayout;
		PBOk = new QPushButton("OK");
		PBCancel = new QPushButton("Cancel");
		connect(PBOk, SIGNAL(clicked()), this, SLOT(Click_ok()));
		connect(PBCancel, SIGNAL(clicked()), this, SLOT(Click_cancel()));
		CBGeometry->addItems(geoComboxList);
		particleLayout->addWidget(LBaseGeometry, 0, 0);
		particleLayout->addWidget(CBGeometry, 0, 1, 1, 2);
		particleLayout->addWidget(LName, 1, 0);
		particleLayout->addWidget(LEName, 1, 1, 1, 2);
		particleLayout->addWidget(LRadius, 2, 0);
		particleLayout->addWidget(LERadius, 2, 1, 1, 2);
		particleLayout->addWidget(PBOk, 3, 0);
		particleLayout->addWidget(PBCancel, 3, 1);
// 		particleLayout->addWidget(LStartPoint, 3, 0);
// 		particleLayout->addWidget(LEStartPoint, 3, 1, 1, 2);
// 		particleLayout->addWidget(LEndPoint, 4, 0);
// 		particleLayout->addWidget(LEEndPoint, 4, 1, 1, 2);
		particleDialog->setLayout(particleLayout);
	}

	particleDialog->exec();
}

void particles::Click_ok()
{
	if (LEName->text().isEmpty()){
		msgBox("Value of name is empty!!", QMessageBox::Critical);
	}
	else if (LERadius->text().isEmpty()){
		msgBox("Value of radius is empty!!", QMessageBox::Critical);
	}
// 	else if (LEStartPoint->text().isEmpty()){
// 		msgBox("Value of start point is empty!!", QMessageBox::Critical);
// 	}
// 	else if (LEEndPoint->text().isEmpty()){
// 		msgBox("Value of end point is empty!!", QMessageBox::Critical);
// 	}

// 	if (!checkParameter3(LEStartPoint)){
// 		msgBox("Start point is wrong data.", QMessageBox::Critical);
// 		return;
// 	}
// 	else if (!checkParameter3(LEEndPoint)){
// 		msgBox("End point is wrong data.", QMessageBox::Critical);
// 		return;
// 	}

	baseGeometry = CBGeometry->currentText();

	Object::name = LEName->text();

	radius = LERadius->text().toFloat();

// 	QStringList chList = LEStartPoint->text().split(" ");
// 	minPoint[0] = chList.at(0).toFloat();
// 	minPoint[1] = chList.at(1).toFloat();
// 	minPoint[2] = chList.at(2).toFloat();
// 
// 	chList = LEEndPoint->text().split(" ");
// 	maxPoint[0] = chList.at(0).toFloat();
// 	maxPoint[1] = chList.at(1).toFloat();
// 	maxPoint[2] = chList.at(2).toFloat();

	particleDialog->close();

	delete particleDialog;
	particleDialog = NULL;
}

void particles::Click_cancel()
{
	LEName->text().clear();
	LERadius->text().clear();
}