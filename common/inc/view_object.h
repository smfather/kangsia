#ifndef VIEW_OBJECT_H
#define VIEW_OBJECT_H

#include "Object.h"
#include "algebra/vector.hpp"

typedef struct
{
	vector3<double> sp;
	vector3<double> ep;
	vector3<double> nor;
}sline;

namespace parview
{
	class object : public Object
	{
	public:
		object();
		virtual ~object();

		void setObjectData(QFile& pf);

		void draw_object();
		virtual void callDialog() {}
		virtual void draw();
		virtual void define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf){}

	private:
		algebra::vector<sline> lines;
		algebra::vector<algebra::vector3<double>> points;

		vector3<float> position;
		vector3<float> velocity;
		//vector3<double> position[MAX_FRAME];
		GLint glList;
	};
}


#endif