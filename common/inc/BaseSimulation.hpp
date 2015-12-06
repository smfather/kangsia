#ifndef BASESIMULATION_HPP
#define BASESIMULATION_HPP
#include <QObject>
#include <map>
#include "types.h"

namespace parview{
	class particles;
	class Object;
}

template <typename base_type>
class BaseSimulation : public QObject
{
public:
	BaseSimulation()
	{
		gravity[0] = 0.0f;
		gravity[1] = -9.80665f;
		gravity[2] = 0.0f;
	}
	~BaseSimulation(){}

	unsigned int& SaveStep() { return saveStep; }
	base_type& SimulationTime() { return simTime; }
	base_type& TimeStep() { return dt; }
	void insertContactObject(parview::Object* obj1, parview::Object* obj2)
	{
		std::map<parview::Object*, parview::Object*>::iterator it = pairContact.find(obj1);
		if (it != pairContact.end()){
			pairContact[obj2] = obj1;
		}
		else{
			pairContact[obj1] = obj2;
		}
	}
	std::map<parview::Object*, parview::Object*>& PairContact() { return pairContact; }
	std::map<QString, contactConstant>& ContactConstants() { return cconts; }

protected:
	void setContactCoefficient(cmaterialType m1, cmaterialType m2)
	{

	}
	virtual void CpuRun() = 0;
	virtual void GpuRun() = 0;
	unsigned int saveStep;
	base_type simTime;
	base_type dt;
	base_type gravity[3];	

	std::map<parview::Object*, parview::Object*> pairContact;
	std::map<QString, contactConstant> cconts;
};

#endif