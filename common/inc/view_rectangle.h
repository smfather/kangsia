#ifndef VIEW_RECTANGLE_H
#define VIEW_RECTANGLE_H

#include "Object.h"

namespace parview
{
	class rectangle : public Object
	{
	public:
		rectangle();
		virtual ~rectangle();

		void setRectangleData(QFile& pf, unsigned int fdtype);
		virtual void callDialog() {}
		virtual void draw();
		virtual void define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf){}
		vector3<float> points[4];

		unsigned int glList;
	};
}

#endif