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
		float startPoint[3];
		float endPoint[3];

		unsigned int glList;
	};
}

#endif