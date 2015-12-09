#ifndef VIEW_BONDDATA_H
#define VIEW_BONDDATA_H

#include "Object.h"

namespace parview
{
	class bondData : public Object
	{
		struct bond_data
		{
			bool broken;
			float length;
			vector3<float> sp;
			vector3<float> ep;
		};

	public:
		bondData();
		virtual ~bondData();

		void setBondData(QFile& pf);

		virtual void callDialog() {}
		virtual void draw();
		virtual void define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf, unsigned int fdtype){}
		bond_data *bds;
		unsigned int size;

		unsigned int glList;
	};
}

#endif