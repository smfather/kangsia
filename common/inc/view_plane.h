#ifndef VIEW_PLANE_H
#define VIEW_PLANE_H

#include "Object.h"

namespace parview
{
	class plane : public Object
	{
	public :
		plane();
		virtual ~plane() {}
		save_plane_info& info_plane() { return spi; }
		virtual void callDialog() {}
		virtual void draw();
		virtual void define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf){}

	private:
		save_plane_info spi;
		unsigned int glList;
	};
}

#endif