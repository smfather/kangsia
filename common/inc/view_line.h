#ifndef VIEW_LINE_H
#define VIEW_LINE_H

#include "Object.h"


namespace parview
{
	class line : public Object
	{
	public:
		line();
		virtual ~line();

		void setLineData(QFile& pf);
		virtual void callDialog() {}
		virtual void draw();
		virtual void define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf){}
		vector3<float> startPoint;
		vector3<float> endPoint;

		unsigned int glList;
	};
}

#endif