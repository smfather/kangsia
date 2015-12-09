#pragma once

#include "Object.h"


using namespace algebra;

namespace parview
{
	class mass;

	class shape : public Object
	{
	public:
		shape();
		virtual ~shape();

		void setShapeData(QFile& pf, unsigned int fdtype = 8);
		
		void draw_shape();
		virtual void callDialog() {}
		virtual void draw();
		virtual void define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf, unsigned int fdtype);

	private:

		GLuint vertice_id;
		GLuint normals_id;
		GLuint indice_id;
		unsigned int v_size;
		unsigned int i_size;

		vector3<float> position;
		vector3<float> *vertice;
		float *normals;
		vector3<unsigned int> *indice;
		
		
	};
}


