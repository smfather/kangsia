#include "view_particles.h"
#include "shader.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QTabWidget>
#include <QDialogButtonBox>

#include "view_cube.h"
#include "view_line.h"

using namespace parview;

//unsigned int particles::current_frame = 0;
//unsigned int particles::buffer_count = 0;
//bool particles::is_play = false;

particles::particles()
	: Object(PARTICLES)
	, np(0)
	, radius(0)
	, maxRadius(0)
	, isSetColor(false)
	, name("particles")
	, isDisplaySupportRadius(false)
	, particleDialog(NULL)
	, isglewinit(false)
{
	//Object::type = NO_GEOMETRY_TYPE;
	for (int i = 0; i < MAX_FRAME; i++){
		pos[i] = NULL;
		vel[i] = NULL;
		pressure[i] = NULL;
		freeSurface[i] = NULL;
		freeSurfaceValue[i] = NULL;

		color[i] = NULL;
	}
	m_posVBO = 0;
	m_colorVBO = 0;
	m_program = 0;
}

particles::~particles()
{
	for (int i = 0; i < MAX_FRAME; i++){
		if (pos[i]) delete [] pos[i]; pos[i] = NULL;
		if (vel[i]) delete [] vel[i]; vel[i] = NULL;
		if (pressure[i]) delete[] pressure[i]; pressure[i] = NULL;
		if (color[i]) delete[] color[i]; color[i] = NULL;
	}

	if (m_program){ glDeleteProgram(m_program); m_program = 0; }
}

void particles::draw_particles()
{
	/*if (view_controller::Play())
		view_controller::move2forward1x();*/
	view_controller::is_end_frame();
	draw(GL_RENDER);
}


void particles::draw(GLenum eMode)
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
	glUniform1f(glGetUniformLocation(m_program, "pointScale"), (*winHeight) / tanf(55 * 0.5f*(float)PI / 180.0f));
	//glUniform1f(glGetUniformLocation(m_program, "pointRadius"), cur_radius);

	//glColor3f(1, 1, 1);
	_drawPoints();

	glUseProgram(0);
	glDisable(GL_POINT_SPRITE_ARB);
	glEnable(GL_LIGHTING);
	emit mySignal();
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

bool particles::define(void* tg)
{
	if (tg != NULL){
		Object *geo = (Object *)tg;

		switch (geo->Type()){
		case LINE:
		{
			parview::line *l = dynamic_cast<line*>(geo);
			algebra::vector3<float> ep(l->endPoint);
			algebra::vector3<float> sp(l->startPoint);
			float len = (ep - sp).length();
			algebra::vector3<float> t = (ep - sp) / len;
			unsigned int _np = (int)floor(len / (radius * 2)) + 1;
			float spacing = (len - (radius * 2) * (_np - 1)) / (_np - 1);
			if (!pos[0])
				pos[0] = new float[_np * 4];
			if (!vel[0])
				vel[0] = new float[_np * 4];
			if (!color[0])
				color[0] = new float[_np * 4];
			for (unsigned int i = np, j = 0; j < _np; i++, j++){
				algebra::vector4<float> p(sp + j*(radius * 2.0f + spacing) * t, radius);
				pos[0][i * 4 + 0] = p.x; vel[0][i * 4 + 0] = 0.0f;
				pos[0][i * 4 + 1] = p.y; vel[0][i * 4 + 1] = 0.0f;
				pos[0][i * 4 + 2] = p.z; vel[0][i * 4 + 2] = 0.0f;
				pos[0][i * 4 + 3] = p.w; vel[0][i * 4 + 3] = 0.0f;
				if (maxRadius < p.w)
					maxRadius = p.w;
				algebra::vector4<float> clr = colors::GetColor(geo->GetColor());
				color[0][i * 4 + 0] = clr.x;
				color[0][i * 4 + 1] = clr.y;
				color[0][i * 4 + 2] = clr.z;
				color[0][i * 4 + 3] = clr.w;
			}
			np += _np;
			geo->SetRoll(ROLL_PARTICLE);
			ctype = geo->GetColor();
			mtype = geo->MaterialType();
			material = geo->Material();
			break;
		}
	}
 	
// 	case CUBE:
// 		{
// 			cube *c = dynamic_cast<cube*>(geo);
// 			algebra::vector3<unsigned int> dim3np = algebra::vector3<unsigned int>(static_cast<unsigned int>(abs(c->width / (radius * 2)))
// 				, static_cast<unsigned int>(abs(c->height / (radius * 2)))
// 				, static_cast<unsigned int>(abs(c->depth / (radius * 2))));
// 			if (dim3np.x == 0) dim3np.x = 1;
// 			if (dim3np.y == 0) dim3np.y = 1;
// 			if (dim3np.z == 0) dim3np.z = 1;
// 
// 			bool bcond = true;
// 			vector3<double> p;
// 			float spacing = radius * 2.1f;
// 			/*np = dim3np.x * dim3np.y * dim3np.z;*/
// 			while (bcond){
// 				bcond = false;
// 				p = vector3<double>(c->minPoint[0] + radius + (dim3np.x - 1) * spacing
// 					, c->minPoint[1] + radius + (dim3np.y - 1) * spacing
// 					, c->minPoint[2] + radius + (dim3np.z - 1) * spacing);
// 				if (p.x + radius > (c->minPoint[0]+c->width) && dim3np.x > 1){
// 					dim3np.x--;
// 					bcond = true;
// 				}
// 				if (p.y + radius > (c->minPoint[1]+c->height) && dim3np.y > 1){
// 					dim3np.y--;
// 					bcond = true;
// 				}
// 				if (p.z + radius > (c->minPoint[2]+c->depth) && dim3np.z > 1){
// 					dim3np.z--;
// 					bcond = true;
// 				}
// 				if (!bcond)
// 					break;
// 			}
// 			np = dim3np.x * dim3np.y * dim3np.z;
// 			srand(1973);
// 			float jitter = radius * 0.001f;
// 			unsigned int p_id = 0;
// 			pos[0] = new float[np * 4];
// 			for (unsigned int z = 0; z < dim3np.z; z++){
// 				for (unsigned int y = 0; y < dim3np.y; y++){
// 					for (unsigned int x = 0; x < dim3np.x; x++){
// 						//double dd = frand();
// 						pos[0][p_id * 4 + 0] = (c->minPoint[0] + radius + x*spacing) + frand()*jitter;
// 						pos[0][p_id * 4 + 1] = (c->minPoint[1] + radius + y*spacing) + frand()*jitter;
// 						pos[0][p_id * 4 + 2] = (c->minPoint[2] + radius + z*spacing) + frand()*jitter;
// 						pos[0][p_id * 4 + 3] = radius;
// 						p_id++;
// 					}
// 				}
// 			}
// 		}
 	}
// 	color[0] = new float[np * 4];
// 	for (unsigned int i = 0; i < np; i++){
// 		color[0][i * 4 + 0] = 0.0f;
// 		color[0][i * 4 + 1] = 0.0f;
// 		color[0][i * 4 + 2] = 1.0f;
// 		color[0][i * 4 + 3] = 1.0f;
// 	}
	if (!np){
		msgBox("Particle generation is failed.", QMessageBox::Critical);
		return false;
	}
	if (!isglewinit)
		glewInit();

	if (m_posVBO){
		glDeleteBuffers(1, &m_posVBO);
		m_posVBO = 0;
	}
	if (m_colorVBO){
		glDeleteBuffers(1, &m_colorVBO);
		m_colorVBO = 0;
	}
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
	if (!m_program)
		m_program = _compileProgram(vertexShader, spherePixelShader);

	return true;
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

void particles::updateDataFromFile(QFile& pf, unsigned int fdtype)
{
	if (fdtype == 8){
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
			double *tmp = new double[np * vecSize];
			pf.read((char*)tmp, sizeof(double) * np * vecSize);
			for (unsigned int i = 0; i < np * vecSize; i++){
				pos[0][i] = (float)tmp[i];
			}
			pf.read((char*)tmp, sizeof(double) * np * vecSize);
			for (unsigned int i = 0; i < np * vecSize; i++){
				vel[0][i] = (float)tmp[i];
			}
			pf.read((char*)isShapeContact, sizeof(bool)*np);
			delete[] tmp;
			for (unsigned int i = 0; i < np; i++){
				if (isShapeContact[i]){
					color[0][i * 4 + 0] = 1.0;
					color[0][i * 4 + 1] = 1.0;
					color[0][i * 4 + 2] = 1.0;
					color[0][i * 4 + 3] = 1.0;
				}
			}
			delete[] isShapeContact;
			return;
		}
	}
	else{
		float time = 0;
		float radius = 0;
		float _pos[3] = { 0, };
		float _vel[3] = { 0, };
		color_type clr;
		int vecSize = 0;

		pf.read((char*)&vecSize, sizeof(int));
		pf.read((char*)&time, sizeof(float));
		pf.read((char*)&np, sizeof(unsigned int));
		bool *isShapeContact = new bool[np];
		if (vecSize == 4){
			pf.read((char*)&clr, sizeof(int));
			pf.read((char*)&radius, sizeof(float));
			pf.read((char*)pos[0], sizeof(float) * np * vecSize);
			pf.read((char*)vel[0], sizeof(float) * np * vecSize);
			pf.read((char*)isShapeContact, sizeof(bool)*np);
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
	}
}

void particles::SetFromFile(QFile& pf, unsigned int _np)
{
	np = _np;
	algebra::vector4<float> *source = new algebra::vector4<float>[np * 5];
	//particle *p = new particle[np];
	if (np){
		pf.read((char*)source, sizeof(algebra::vector4<float>)*np * 5);
		pos[view_controller::getTotalBuffers()] = new float[np * 4];
		vel[view_controller::getTotalBuffers()] = new float[np * 4];
		color[view_controller::getTotalBuffers()] = new float[np * 4];
		pf.read((char*)pos[view_controller::getTotalBuffers()], sizeof(algebra::vector4<float>)*np);
		pf.read((char*)vel[view_controller::getTotalBuffers()], sizeof(algebra::vector4<float>)*np);
		for (unsigned int i = 0; i < np; i++){
			color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
			color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
		}
	}
	else{

	}
	
}

void particles::alloc_buffer_dem(QFile& pf, unsigned int fdtype)
{
	if (fdtype == 4){
		float time = 0.0f;
		float radius = 0.0f;
		color_type clr;
		int vecSize = 0;
		bool *isShapeContact = NULL;
		pf.read((char*)&vecSize, sizeof(int));
		pf.read((char*)&time, sizeof(float));
		pf.read((char*)&np, sizeof(unsigned int));
		pos[view_controller::getTotalBuffers()] = new float[np * 4];
		vel[view_controller::getTotalBuffers()] = new float[np * 4];
		color[view_controller::getTotalBuffers()] = new float[np * 4];
		isShapeContact = new bool[np];
		pf.read((char*)&clr, sizeof(int));
		pf.read((char*)&radius, sizeof(float));
		pf.read((char*)pos[view_controller::getTotalBuffers()], sizeof(float)*np * 4);
		pf.read((char*)vel[view_controller::getTotalBuffers()], sizeof(float)*np * 4);
		pf.read((char*)isShapeContact, sizeof(bool)*np);
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
				color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.7f;
				color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.8f;
				color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
				break;
			}
			if (isShapeContact[i]){
				color[view_controller::getTotalBuffers()][i * 4 + 0] = 1.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
			}
		}
		delete[] isShapeContact;
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
					color[view_controller::getTotalBuffers()][i * 4 + 0] = 1.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
					color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
				}
			}
			delete[] isShapeContact;
		}
		else{
			double *tmp = new double[vecSize];
			for (unsigned int i = 0; i < np; i++){
				pf.read((char*)&clr, sizeof(int));
				// 				switch (clr){
				// 				case RED:
				// 					color[view_controller::getTotalBuffers()][i * 4 + 0] = 1.0f;
				// 					color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
				// 					color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
				// 					color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
				// 					break;
				// 				case GREEN:
				color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 1] = 1.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 2] = 0.0f;
				color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
				// 					break;
				// 				case BLUE:
				// 					color[view_controller::getTotalBuffers()][i * 4 + 0] = 0.0f;
				// 					color[view_controller::getTotalBuffers()][i * 4 + 1] = 0.0f;
				// 					color[view_controller::getTotalBuffers()][i * 4 + 2] = 1.0f;
				// 					color[view_controller::getTotalBuffers()][i * 4 + 3] = 1.0f;
				// 					break;
				// 				}
				pf.read((char*)&radius, sizeof(double));
				pf.read((char*)tmp, sizeof(double)*vecSize);
				pos[view_controller::getTotalBuffers()][i * 4 + 0] = tmp[0];
				pos[view_controller::getTotalBuffers()][i * 4 + 1] = tmp[1];
				pos[view_controller::getTotalBuffers()][i * 4 + 2] = tmp[2];
				pos[view_controller::getTotalBuffers()][i * 4 + 3] = radius;
				pf.read((char*)tmp, sizeof(double)*vecSize);
				vel[view_controller::getTotalBuffers()][i * 4 + 0] = tmp[0];
				vel[view_controller::getTotalBuffers()][i * 4 + 1] = tmp[1];
				vel[view_controller::getTotalBuffers()][i * 4 + 2] = tmp[2];
				vel[view_controller::getTotalBuffers()][i * 4 + 3] = 0.0;
			}
			delete[] tmp;
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
	view_controller::addTimes(view_controller::getTotalBuffers(), time);
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

void particles::insert_particle_buffer(float* p, unsigned int n)
{
	view_controller::upBufferCount();
	if(!pos[view_controller::getTotalBuffers()])
		pos[view_controller::getTotalBuffers()] = new float[np * 4];
	if(!vel[view_controller::getTotalBuffers()])
		vel[view_controller::getTotalBuffers()] = new float[np * 4];
	if(!color[view_controller::getTotalBuffers()])
		color[view_controller::getTotalBuffers()] = new float[np * 4];
	memcpy(pos[view_controller::getTotalBuffers()], p, sizeof(float) * n * 4);

	algebra::vector4<float> clr = colors::GetColor(ctype);
	for (unsigned int i = 0; i < n; i++){
		color[view_controller::getTotalBuffers()][i * 4 + 0] = clr.x;
		color[view_controller::getTotalBuffers()][i * 4 + 1] = clr.y;
		color[view_controller::getTotalBuffers()][i * 4 + 2] = clr.z;
		color[view_controller::getTotalBuffers()][i * 4 + 3] = clr.w;
	}
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
// 
// algebra::vector4<float> particles::getPositionToV4(unsigned int id)
// {
// 	unsigned int cf = view_controller::getFrame();
// 	float* outPos = pos[cf];
// 	return algebra::vector4<float>(outPos[id * 4 + 0]
// 								 , outPos[id * 4 + 1]
// 								 , outPos[id * 4 + 2]);
// 	
// }

// algebra::vector4<float> particles::getVelocityToV4(unsigned int id)
// {
// 	unsigned int cf = view_controller::getFrame();
// 	float* outVel = vel[cf];
// 	return algebra::vector4<float>(outVel[id * 3+ 0]
// 		, outVel[id * 3 + 1]
// 		, outVel[id * 3 + 2]);
// }

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

void particles::AddParticleFromManual(float* p, float* v)
{
	float *tpos = new float[(np + 1) * 4];
	float *tvel = new float[(np + 1) * 4];
	float *tclr = new float[(np + 1) * 4];
	memcpy(tpos, pos[view_controller::getFrame()], sizeof(float) * 4 * np);
	memcpy(tvel, pos[view_controller::getFrame()], sizeof(float) * 4 * np);
	memcpy(tclr, pos[view_controller::getFrame()], sizeof(float) * 4 * np);
	tpos[np * 4 + 0] = p[0]; tpos[np * 4 + 1] = p[1]; tpos[np * 4 + 2] = p[2]; tpos[np * 4 + 3] = p[3];
	tvel[np * 4 + 0] = v[0]; tvel[np * 4 + 1] = v[1]; tvel[np * 4 + 2] = v[2]; tvel[np * 4 + 3] = v[3];
	tclr[np * 4 + 0] = Object::color[0]; tclr[np * 4 + 1] = Object::color[1];
	tclr[np * 4 + 2] = Object::color[2]; tclr[np * 4 + 3] = Object::color[3];
	if (maxRadius < p[3])
		maxRadius = p[3];
	if(pos[view_controller::getFrame()])
		delete [] pos[view_controller::getFrame()];
	if(color[view_controller::getFrame()])
		delete [] color[view_controller::getFrame()];
	if(vel[view_controller::getFrame()])
		delete [] vel[view_controller::getFrame()];
	pos[view_controller::getFrame()] = new float[(np + 1) * 4];
	vel[view_controller::getFrame()] = new float[(np + 1) * 4];
	color[view_controller::getFrame()] = new float[(np + 1) * 4];
	memcpy(pos[view_controller::getFrame()], tpos, sizeof(float)*(np + 1) * 4);
	memcpy(vel[view_controller::getFrame()], tvel, sizeof(float)*(np + 1) * 4);
	memcpy(color[view_controller::getFrame()], tclr, sizeof(float)*(np + 1) * 4);
	np = np + 1;
	if(!isglewinit)
		glewInit();
	unsigned int memSize = sizeof(float) * 4 * np;
	if (m_posVBO){
		glDeleteBuffers(1, &m_posVBO); 
		m_posVBO = 0;
	}
	if (m_colorVBO){
		glDeleteBuffers(1, &m_colorVBO);
		m_colorVBO = 0;
	}
	buffer = pos[view_controller::getFrame()];
	color_buffer = color[view_controller::getFrame()];
	if (!m_posVBO)
		m_posVBO = createVBO(memSize, buffer);
	if (!m_colorVBO)
		m_colorVBO = createVBO(memSize, color_buffer);

	if (!m_program)
		m_program = _compileProgram(vertexShader, spherePixelShader);
}

void particles::AddParticlesFromFile(QFile& pf)
{
	unsigned int addnp = 742500;
	//pf.read((char*)&addnp, sizeof(unsigned int));
	vector3<double> *ttpos = new vector3<double>[addnp];
	float *tpos = new float[(np + addnp) * 4];
	float *tclr = new float[(np + addnp) * 4];
	memcpy(tpos, pos[view_controller::getFrame()], sizeof(float) * 4 * np);
	memcpy(tclr, color[view_controller::getFrame()], sizeof(float) * 4 * np);
	pf.read((char*)ttpos, sizeof(double) * 3 * addnp);
	for (unsigned int i = np; i < addnp + np; i++){

		tpos[i * 4 + 0] = (float)ttpos[i - np].x;
		tpos[i * 4 + 1] = (float)ttpos[i - np].y;
		tpos[i * 4 + 2] = (float)ttpos[i - np].z;
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
	memcpy(pos[view_controller::getFrame()], tpos, sizeof(float)*(np + addnp) * 4);
	memcpy(color[view_controller::getFrame()], tclr, sizeof(float)*(np + addnp) * 4);
	np = np + addnp;
	delete[] tpos;
	delete[] tclr;
	delete[] ttpos;

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

bool particles::callDialog(DIALOGTYPE dt)
{
	if (!particleDialog){
		particleDialog = new QDialog;
		tabWidget = new QTabWidget;
		byGeoTab = new QWidget;
		byManualTab = new QWidget;
		QLabel *LBaseGeometry = new QLabel("Base geometry");
		CBGeometry = new QComboBox;
		QLabel *LName = new QLabel("Name");
		LEName = new QLineEdit;
		LEName->setText("particles");
		LEName->setReadOnly(true);
		QLabel *LRadius = new QLabel("Radius");
		QLabel *LMRadius = new QLabel("Radius");
		LERadius = new QLineEdit;
		LEMRadius = new QLineEdit;
		QGridLayout *byGeoLayout = new QGridLayout;
		CBGeometry->addItems(geoComboxList);
		byGeoLayout->addWidget(LBaseGeometry, 0, 0); byGeoLayout->addWidget(CBGeometry, 0, 1, 1, 2);
		byGeoLayout->addWidget(LName, 1, 0); byGeoLayout->addWidget(LEName, 1, 1, 1, 2);
		byGeoLayout->addWidget(LRadius, 2, 0); byGeoLayout->addWidget(LERadius, 2, 1, 1, 2);
		byGeoTab->setLayout(byGeoLayout);
		tabWidget->addTab(byGeoTab, "Geometry"); byGeoTab->setObjectName("Geometry");
		QLabel *LPosition = new QLabel("Position");
		LEPosition = new QLineEdit;
		QLabel *LVelocity = new QLabel("Velocity");
		LEVelocity = new QLineEdit;
		QGridLayout *byManualLayout = new QGridLayout;
		byManualLayout->addWidget(LMaterial, 0, 0);
		byManualLayout->addWidget(CBMaterial, 0, 1, 1, 2);
		byManualLayout->addWidget(LPosition, 1, 0);
		byManualLayout->addWidget(LEPosition, 1, 1, 1, 2);
		byManualLayout->addWidget(LVelocity, 2, 0);
		byManualLayout->addWidget(LEVelocity, 2, 1, 1, 2);
		byManualLayout->addWidget(LMRadius, 3, 0);
		byManualLayout->addWidget(LEMRadius, 3, 1, 1, 2);
		byManualTab->setLayout(byManualLayout);
		tabWidget->addTab(byManualTab, "Manual"); byManualTab->setObjectName("Manual");
		QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
		connect(buttonBox, SIGNAL(accepted()), this, SLOT(Click_ok()));
		connect(buttonBox, SIGNAL(rejected()), this, SLOT(Click_cancel()));
		QVBoxLayout *mainLayout = new QVBoxLayout;
		mainLayout->addWidget(tabWidget);
		mainLayout->addWidget(buttonBox);
		particleDialog->setLayout(mainLayout);
	}

	particleDialog->exec();
	return isDialogOk ? true : false;
}

void particles::Click_ok()
{
	bool isManual;
	float p[4] = { 0, };
	float v[4] = { 0, };
	QWidget *cTab = tabWidget->currentWidget();
	QString on = cTab->objectName();
	if (on == "Geometry"){
		if (LEName->text().isEmpty()){
			msgBox("Value of name is empty!!", QMessageBox::Critical);
			return;
		}
		if (LERadius->text().isEmpty()){
			msgBox("Value of radius is empty!!", QMessageBox::Critical);
			return;
		}
		baseGeometry = CBGeometry->currentText();
		Object::name = LEName->text();
		isManual = false;
		radius = LERadius->text().toFloat();
// 		QString comm;
// 		QTextStream(&comm) << "Create Geometry " << baseGeometry << " " << radius << "\n";
	}
	else if(on == "Manual"){
		QStringList ss;// = LEPa->text().split(",");
		if (LEMRadius->text().isEmpty()){
			msgBox("Value of radius is empty!!", QMessageBox::Critical);
			return;
		}
		if (LEPosition->text().split(",").size() == 3)
			ss = LEPosition->text().split(",");
		else
			if (LEPosition->text().split(" ").size() == 3)
				ss = LEPosition->text().split(" ");
			else
				if (LEPosition->text().split(", ").size() == 3)
					ss = LEPosition->text().split(", ");
				else {
					msgBox("Position is wrong data.", QMessageBox::Critical);
					return;
				}
		p[0] = ss.at(0).toFloat(); p[1] = ss.at(1).toFloat(); p[2] = ss.at(2).toFloat();

		if (LEVelocity->text().split(",").size() == 3)
			ss = LEVelocity->text().split(",");
		else
			if (LEVelocity->text().split(" ").size() == 3)
				ss = LEVelocity->text().split(" ");
			else
				if (LEVelocity->text().split(", ").size() == 3)
					ss = LEVelocity->text().split(", ");
				else{
					msgBox("Velocity is wrong data.", QMessageBox::Critical);
					return;
					}
		v[0] = ss.at(0).toFloat(); v[1] = ss.at(1).toFloat(); v[2] = ss.at(2).toFloat();
		isManual = true;
		baseGeometry = "none";
		Object::name = "particles";
		radius = p[3] = LEMRadius->text().toFloat();
		mtype = material_str2enum(CBMaterial->currentText().toStdString());
		material = getMaterialConstant(mtype);
		AddParticleFromManual(p, v);
// 		QString comm;
// 		QTextStream(&comm) 
// 			<< "Create Manual " << radius << " " << (int)mtype << " "
// 			<< p[0] << " " << p[1] << " " << p[2] << " "
// 			<< v[0] << " " << p[1] << " " << p[2] << "\n";
// 		cpProcess.push_back(comm);
	}

	particleDialog->close();

	delete particleDialog;
	particleDialog = NULL;
	isDialogOk = true;
}

void particles::Click_cancel()
{
	particleDialog->close();
	delete particleDialog; particleDialog = NULL;
	isDialogOk = false;
}

void particles::SaveObject(QTextStream& out)
{
 	out << "OBJECT" << " " << "PARTICLES" << " " << name << "\n";
	out << np << " " << radius << " " << (int)mtype << "\n";
	QFile pio(modeler::modelPath() + modeler::modelName() + "/particles.par");
	pio.open(QIODevice::WriteOnly);
	pio.write((char*)pos[0], sizeof(float) * 4 * np);
	pio.write((char*)vel[0], sizeof(float) * 4 * np);
	pio.write((char*)particles::color[0], sizeof(float) * 4 * np);
	pio.close();
	// 	for (unsigned int i = 0; i < cpProcess.size(); i++){
// 		out << cpProcess.at(i);
// 	}
 	//out << baseGeometry << " " << radius << "\n";
}

void particles::SetDataFromFile(QTextStream& in)
{
	unsigned int _np = 0;
	float _rad = 0;
	int mt = 0;
	in >> name >> np >> radius >> mt; 
	QFile pout(modeler::modelPath() + modeler::modelName() + "/particles.par");
	pout.open(QIODevice::ReadOnly);
	if (pos[0])
		delete[] pos[0];
	if (vel[0])
		delete[] vel[0];
	if (color[0])
		delete[] color[0];
	pos[0] = new float[np * 4];
	vel[0] = new float[np * 4];
	color[0] = new float[np * 4];
	pout.read((char*)pos[0], sizeof(float)*np * 4);
	pout.read((char*)vel[0], sizeof(float)*np * 4);
	pout.read((char*)color[0], sizeof(float)*np * 4);
	pout.close();
	mtype = (material_type)mt;
	material = getMaterialConstant(mtype);
// 	if (op == "Create"){
// 		if (ct == "Manual"){
// 			baseGeometry = "none";
// 			Object::name = "particles";
// 			int mt;
// 			float p[4] = { 0, };
// 			float v[4] = { 0, };
// 			in >> p[3] >> mt >> p[0] >> p[1] >> p[2] >> v[0] >> v[1] >> v[2];
// 			radius = p[3];
// 			mtype = (material_type)mt;
// 			material = getMaterialConstant(mtype);
// 			AddParticleFromManual(p, v);
// 			QString comm;
// 			QTextStream(&comm)
// 				<< "Create Manual " << radius << " " << (int)mtype << " "
// 				<< p[0] << " " << p[1] << " " << p[2] << " "
// 				<< v[0] << " " << v[1] << " " << v[2] << "\n";
// 			cpProcess.push_back(comm);
// 		}
// 		else if (ct == "Geometry"){
// 			in >> baseGeometry >> radius;
// 		}
// 	}
}