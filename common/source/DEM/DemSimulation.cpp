#include "DEM/DemSimulation.h"
#include "view_particles.h"
#include <QtWidgets>


DemSimulation::DemSimulation()
{

}

DemSimulation::~DemSimulation()
{

}

bool DemSimulation::Initialize(std::map<QString, parview::Object*>& objs)
{
	std::map<QString, parview::Object*>::iterator it = objs.find("particles");
	viewPars = dynamic_cast<parview::particles*>(it->second);
	std::map<QString, QString> pairContact;
	pairContact[viewPars->Name()] = viewPars->Name();

	for (it = objs.begin(); it != objs.end(); it++){
		if (it->first != "Particles"){
			pairContact[it->second->Name()] = viewPars->Name();
			BaseSimulation::contactObject.push_back(it->second);
		}
	}

	// Input Contact Coefficient Table
	QWidget ccWidget;
	QTableWidget cctable(pairContact.size(), 5);
	cctable.setSelectionBehavior(QAbstractItemView::SelectRows);
	QStringList labels;
	labels << tr("Spring Const.(kn)") << tr("Damping Coef.(vn)") << tr("Friction") << tr("Restitution coef.") << tr("Ratio(ks/kn)");
	cctable.setHorizontalHeaderLabels(labels);
	cctable.verticalHeader()->hide();
	cctable.setShowGrid(true);

	QGridLayout mainLayout;
	mainLayout.setSizeConstraint(QLayout::SetNoConstraint);
	mainLayout.addWidget(&cctable, 0, 0);
	ccWidget.setLayout(&mainLayout);
	ccWidget.setWindowTitle("Input Contact Coefficient Table");
	ccWidget.resize(700, 300);
	ccWidget.setWindowModality(Qt::WindowModality::ApplicationModal);
	ccWidget.show();
	
	return true;
}

void DemSimulation::CpuRun()
{

}

void DemSimulation::GpuRun()
{

}