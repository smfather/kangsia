#ifndef VIEW_MASS
#define VIEW_MASS

#include "Object.h"


namespace parview
{
	class mass : public Object
	{
	public:
		mass();
		virtual ~mass();

		void setMassData(QFile& pf);
		float* Position(unsigned int i) { return &pos[i].x; }
		float* Velocity(unsigned int i) { return &vel[i].x; }
		vector3<float>& Force(unsigned int i) { return force[i]; }
		virtual void callDialog() {}
		virtual void draw();
		virtual void define(void* tg = 0);
		virtual void saveCurrentData(QFile& pf);
		virtual void updateDataFromFile(QFile& pf);

	private:
		vector3<float> pos[MAX_FRAME];
		vector3<float> vel[MAX_FRAME];
		vector3<float> force[MAX_FRAME];
	};
}

#endif