#include "parview.h"
#include "view_particles.h"
#include "view_controller.h"
#include "solveDialog.h"
#include "contactCoefficientTable.h"
#include <QtWidgets>
#include <QFileDialog.h>

using namespace parview;

parVIEW::parVIEW(QWidget *parent)
	: QMainWindow(parent)
	, dem(NULL)
{
	pinfoDialog = NULL;
	animation_statement = false;
	ui.setupUi(this);
	gl = new GLWidget(NULL);
	ui.GraphicArea->setWidget(gl);
	QMainWindow::show();

	newAct = new QAction(QIcon(":/image/new.png"), tr("&New"), this);
	newAct->setStatusTip(tr("New"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newproj()));

	openAct = new QAction(QIcon(":/image/open.png"), tr("&Open"), this);
	openAct->setStatusTip(tr("Open project"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openproj()));

	openRtAct = new QAction(QIcon(":/image/open_rt.png"), tr("&Open_rt"), this);
	openRtAct->setStatusTip(tr("Open real time"));
	connect(openRtAct, SIGNAL(triggered()), this, SLOT(openrtproj()));

	saveAct = new QAction(QIcon(":/image/save.png"), tr("&Save"), this);
	saveAct->setStatusTip(tr("Save project"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveproj()));

	pinfoAct = new QAction(QIcon(":/image/ani_play.png"), tr("&Particle info dialog"), this);
	pinfoAct->setStatusTip(tr("Particle info dialog"));
	connect(pinfoAct, SIGNAL(triggered()), this, SLOT(openPinfoDialog()));

	makeRectAct = new QAction(QIcon(":/image/icRect.png"), tr("&Create Rectangle Object"), this);
	makeRectAct->setStatusTip(tr("Create Rectangle Object"));
	connect(makeRectAct, SIGNAL(triggered()), this, SLOT(makeRect()));

	makeLineAct = new QAction(QIcon(":/image/icLine.png"), tr("&Create Line Object"), this);
	makeLineAct->setStatusTip(tr("Create Line Object"));
	connect(makeLineAct, SIGNAL(triggered()), this, SLOT(makeLine()));

	makeParticleAct = new QAction(QIcon(":/image/particle.png"), tr("&Create particles"), this);
	makeParticleAct->setStatusTip(tr("Create particles"));
	connect(makeParticleAct, SIGNAL(triggered()), this, SLOT(makeParticle()));

	collidConstAct = new QAction(QIcon(":/image/collision.png"), tr("&Define contact constant"), this);
	collidConstAct->setStatusTip(tr("Define contact constant"));
	connect(collidConstAct, SIGNAL(triggered()), this, SLOT(collidConst()));

	solveProcessAct = new QAction(QIcon(":/image/solve.png"), tr("&Solve the model"), this);
	solveProcessAct->setStatusTip(tr("Solve the model"));
	connect(solveProcessAct, SIGNAL(triggered()), this, SLOT(solveProcess()));

	connect(ui.actionChange_Shape, SIGNAL(triggered()), this, SLOT(ChangeShape()));

	ui.mainToolBar->addAction(newAct);
	ui.mainToolBar->addAction(openAct);
	ui.mainToolBar->addAction(openRtAct);
	ui.mainToolBar->addAction(saveAct);
	ui.mainToolBar->addAction(pinfoAct);
	ui.mainToolBar->addAction(makeRectAct);
	ui.mainToolBar->addAction(makeLineAct);
	ui.mainToolBar->addAction(makeParticleAct);
	ui.mainToolBar->addAction(collidConstAct);
	ui.mainToolBar->addAction(solveProcessAct);

	viewObjectComboBox = new QComboBox;
	viewObjectComboBox->insertItem(0, "All display");
	viewObjectComboBox->insertItem(1, "Only frame");
	viewObjectComboBox->insertItem(2, "Only particle");
	connect(viewObjectComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeComboBox(int)));
	ui.secToolBar->addWidget(viewObjectComboBox);

	aniPreviousAct2 = new QAction(QIcon(":/image/ani_moreprevious.png"), tr("&previous2x"), this);
	aniPreviousAct2->setStatusTip(tr("2x previous for animation."));
	connect(aniPreviousAct2, SIGNAL(triggered()), this, SLOT(ani_previous2x()));

	aniPreviousAct = new QAction(QIcon(":/image/ani_previous.png"), tr("&previous1x"), this);
	aniPreviousAct->setStatusTip(tr("1x previous for animation."));
	connect(aniPreviousAct, SIGNAL(triggered()), this, SLOT(ani_previous1x()));

	aniPlayAct = new QAction(QIcon(":/image/ani_play.png"), tr("&play"), this);
	aniPlayAct->setStatusTip(tr("play for animation."));
	connect(aniPlayAct, SIGNAL(triggered()), this, SLOT(ani_play()));

	aniForwardAct = new QAction(QIcon(":/image/ani_fast.png"), tr("&forward1x"), this);
	aniForwardAct->setStatusTip(tr("1x forward for animation."));
	connect(aniForwardAct, SIGNAL(triggered()), this, SLOT(ani_forward1x()));

	aniForwardAct2 = new QAction(QIcon(":/image/ani_morefast.png"), tr("&forward2x"), this);
	aniForwardAct2->setStatusTip(tr("2x forward for animation."));
	connect(aniForwardAct2, SIGNAL(triggered()), this, SLOT(ani_forward2x()));

	ui.secToolBar->addAction(aniPreviousAct2);
	ui.secToolBar->addAction(aniPreviousAct);
	ui.secToolBar->addAction(aniPlayAct);
	ui.secToolBar->addAction(aniForwardAct);
	ui.secToolBar->addAction(aniForwardAct2);

	HSlider = new QSlider(Qt::Orientation::Horizontal, this);
	
	HSlider->setFixedWidth(100);
	connect(HSlider, SIGNAL(valueChanged(int)), this, SLOT(ani_scrollbar()));
	ui.secToolBar->addWidget(HSlider);

	LEframe = new QLineEdit(this);
	LEframe->setText(QString("0"));
	LEframe->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	LEframe->setFixedWidth(50);
	LEframe->setContentsMargins(QMargins(5, 0, 0, 0));
	ui.secToolBar->addWidget(LEframe);
	Lframe = new QLabel(this);
	Lframe->setText(QString("/ 0"));
	Lframe->setContentsMargins(QMargins(5, 0, 0, 0));
	ui.secToolBar->addWidget(Lframe);
	LETimes = new QLineEdit(this);
	LETimes->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	LEframe->setFixedWidth(50);
	LETimes->setFixedWidth(50);
	QLabel *LTimes = new QLabel(this);
	LTimes->setText(QString("Time : "));
	LTimes->setContentsMargins(QMargins(10, 0, 0, 0));
	ui.secToolBar->addWidget(LTimes);
	ui.secToolBar->addWidget(LETimes);
}

parVIEW::~parVIEW()
{
	if (gl) delete gl; gl = NULL;
	if (pinfoDialog) delete pinfoDialog; pinfoDialog = NULL;
}

void parVIEW::ChangeComboBox(int id)
{
	gl->ChangeDisplayOption(id);
}

void parVIEW::newproj()
{
	QString dir = "C:/";
	QString fileName = QFileDialog::getOpenFileName(this, tr("open"), dir);
	if (fileName.isEmpty())
		return;

	gl->AddBondData(fileName);
	//gl->AddParticles(fileName);
}

void parVIEW::openrtproj()
{
	QString dir = "C:/";
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("open"), dir);
	if (fileNames.isEmpty())
		return;
	gl->getDemFileData(fileNames, true);
	QString tf;
	tf.sprintf("/ %d", view_controller::getTotalBuffers() - 1);
	Lframe->setText(tf);
	HSlider->setMaximum(view_controller::getTotalBuffers() - 1);
	//particle_ptr = gl->getParticle_ptr();
	if (gl->getParticle_ptr()){
		connect(gl->getParticle_ptr(), SIGNAL(mySignal()), this, SLOT(mySlot()));
	}
	view_controller::setRealTimeParameter(true);
}

// CODEDYN
void parVIEW::openproj()
{
	QString dir = "C:/";
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("open"), dir);
	if (fileNames.isEmpty())
		return;
	if (fileNames.size() == 1){
		QString file = fileNames.at(0);
		int begin = file.lastIndexOf(".");
		QString ext = file.mid(begin);
		if (ext == ".txt"){
			gl->OpenTXT_file(file);
		}
	}
	gl->OpenFiles(fileNames);
}

// BEFORE CODEDYN
// void parVIEW::openproj()
// {
// 	QString dir = "C:/";
// 	//QString dir_name = QFileDialog::getOpenDirectoryName(this, tr("open"), dir);
// 	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("open"), dir);
// 
// 	//QString fileNames = QFileDialog::getOpenFileName(this, tr("open"), dir);
// 	if (fileNames.isEmpty())
// 		return;
// 
// 	//gl->getSphFileData(fileNames);
// 	gl->getDemFileData(fileNames, false);
// 	//QFile file(fileNames);
// 	//if (file.open(QIODevice::ReadOnly)){
// 	//	gl->getFileData(file);
// 	//	//gl->getSphFileData(file);
// 	//}
// 	//file.close();
// 
// 	QString tf;
// 	tf.sprintf("/ %d", view_controller::getTotalBuffers() - 1);
// 	Lframe->setText(tf);
// 	HSlider->setMaximum(view_controller::getTotalBuffers() - 1);
// 	//particle_ptr = gl->getParticle_ptr();
// 	if (gl->getParticle_ptr()){
// 		connect(gl->getParticle_ptr(), SIGNAL( mySignal() ), this, SLOT(mySlot()));
// 	}
// }

void parVIEW::saveproj()
{
	QString dir = "C:/";
	QString fileName = QFileDialog::getSaveFileName(this, tr("save"), dir);
	if (fileName.isEmpty())
		return;
	QFile file(fileName);
	if (file.open(QIODevice::WriteOnly)){
		gl->SaveModel(file);
	}
	file.close();
}

void parVIEW::mySlot()
{
	int cf = view_controller::getFrame();
	HSlider->setValue(cf);
	QString str;
	str.sprintf("%d", cf);
	LEframe->setText(str);
}

void parVIEW::ani_previous2x()
{
	if (gl->is_set_particle()){
		ani_pause();
		view_controller::move2previous2x();
		QString tf;
		tf.sprintf("%.5f", view_controller::getTimes());
		LETimes->setText(tf);
	}	
}

void parVIEW::ani_previous1x()
{
	if (gl->is_set_particle()){
		ani_pause();
		view_controller::move2previous1x();
		QString tf;
		tf.sprintf("%.5f", view_controller::getTimes());
		LETimes->setText(tf);
	}	
}

void parVIEW::ani_play()
{
	animation_statement = true;
	if (gl->is_set_particle()){
		view_controller::on_play();
		QString tf;
		tf.sprintf("%.5f", view_controller::getTimes());
		LETimes->setText(tf);
	}
	
	if (view_controller::is_end_frame())
		return;

	disconnect(aniPlayAct);
	aniPlayAct->setIcon(QIcon(":/image/ani_pause.png"));
	aniPlayAct->setStatusTip(tr("Pause for animation."));
	connect(aniPlayAct, SIGNAL(triggered()), this, SLOT(ani_pause()));


	/*objects->setAnimationState(ANIMATION_PLAY);*/
}

void parVIEW::ani_pause()
{
	animation_statement = false;
	view_controller::off_play();
	disconnect(aniPlayAct);
	aniPlayAct->setIcon(QIcon(":/image/ani_play.png"));
	aniPlayAct->setStatusTip(tr("Play for animation."));
	connect(aniPlayAct, SIGNAL(triggered()), this, SLOT(ani_play()));
}

void parVIEW::ani_forward1x()
{
	if (gl->is_set_particle()) {
		ani_pause();
		view_controller::move2forward1x();
		QString tf;
	//	double t = view_controller::getTimes();
		tf.sprintf("%.5f", view_controller::getTimes());
		LETimes->setText(tf);
	}
}

void parVIEW::ani_forward2x()
{
	if (gl->is_set_particle()) {
		ani_pause();
		view_controller::move2forward2x();
		QString tf;
		tf.sprintf("%.5f", view_controller::getTimes());
		LETimes->setText(tf);
	}
}

void parVIEW::ani_scrollbar()
{
	if (animation_statement){
		QString tf;
		tf.sprintf("%.5f", view_controller::getTimes());
		LETimes->setText(tf);
		return;
	}

	int value = HSlider->value();
	QString str;
	str.sprintf("%d", value);
	LEframe->setText(str);
	if (gl->is_set_particle()) {
		view_controller::setFrame(unsigned int(value));
		if (view_controller::getRealTimeParameter())
			gl->UpdateRtDEMData();
	}
}

void parVIEW::openPinfoDialog()
{
	if (animation_statement)
		return;
	if (gl->is_set_particle()){
		if (!pinfoDialog)
			pinfoDialog = new particleInfoDialog(this);

		pinfoDialog->bindingParticleViewer(gl->getViewParticle());
		pinfoDialog->show();
		pinfoDialog->raise();
		pinfoDialog->activateWindow();
	}

}

void parVIEW::ChangeShape()
{
	QString dir = "C:/C++/add_particle.bin";
	//QString fileName = QFileDialog::getOpenFileName(this, tr("open"), dir);
	//if (fileName.isEmpty())
	//	return;
	//gl->ChangeShapeData(fileName);

	gl->ExportForceData();
	//gl->AddParticles(dir);
}

void parVIEW::makeCube()
{
	gl->makeCube();
}

void parVIEW::makeRect()
{
	gl->makeRect();
}

void parVIEW::makeLine()
{
	gl->makeLine();
}

void parVIEW::makeParticle()
{
	gl->makeParticle();
}

void parVIEW::collidConst()
{
	gl->defineCollidConst();
}

void parVIEW::solveProcess()
{
	QMessageBox msgBox;
	if (!dem){
		dem = new DemSimulation(gl);
	}
	std::map<QString, parview::Object*>::iterator itp = gl->Objects().find("particles");
	parview::particles *viewPars = dynamic_cast<parview::particles*>(itp->second);
	if (itp == gl->Objects().end()){
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("First, create the particles!!");
		msgBox.exec();
	}
	std::map<QString, QString> pairContact;
	dem->insertContactObject(itp->second, itp->second);
	//pairContact[itp->second->Name()] = itp->second->Name();
	for (std::map<QString, parview::Object*>::iterator it = gl->Objects().begin(); it != gl->Objects().end(); it++){
		if (it->first != "particles"){
			if (it->first == viewPars->BaseGeometryText()){
				continue;
			}
			dem->insertContactObject(itp->second, it->second);
		}
	}

// 	contactCoefficientTable cct;
// 	cct.setTable(dem->PairContact());
// 	cct.exec();

	dem->ContactConstants(gl->ContactConstants());
	solveDialog solDlg(gl);
	if (solDlg.callDialog()){
		//connect(dem, SIGNAL(mySignal(int)), this, SLOT(mySlot(int)));
		dem->SimulationTime() = solDlg.simTime;
		dem->SaveStep() = solDlg.saveTime;
		dem->TimeStep() = solDlg.timeStep;

		if (dem->Initialize(/*gl->Objects()*/)){
			ui.statusBar->addWidget(dem->GetProgressBar());
			dem->CpuRun();
		}
		ui.statusBar->removeWidget(dem->GetProgressBar());
	}
	
	delete dem;
}

