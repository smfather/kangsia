#include "dhspring.h"
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>

DHSpring::DHSpring(QWidget *parent)
	: QMainWindow(parent)
	, rTable(NULL)
	, springImageDialog(NULL)
{
	ui.setupUi(this);
	connect(ui.analyzeButton, SIGNAL(clicked()), this, SLOT(actionAnalyze()));
	connect(ui.PB_result, SIGNAL(clicked()), this, SLOT(actionResultTable()));
	connect(ui.LE_Free_length_Value, SIGNAL(editingFinished()), this, SLOT(setInitCompression()));
	connect(ui.LE_inst_length, SIGNAL(editingFinished()), this, SLOT(setInitCompression()));
	connect(ui.LE_stroke, SIGNAL(editingFinished()), this, SLOT(setTotalCompression()));
	connect(ui.LE_D_Value, SIGNAL(editingFinished()), this, SLOT(setInerOuterDiameter()));
	connect(ui.LE_d_Value, SIGNAL(editingFinished()), this, SLOT(setInerOuterDiameter()));
	connect(ui.LE_N_value, SIGNAL(editingFinished()), this, SLOT(checkN()));
	connect(ui.LE_D_Value, SIGNAL(editingFinished()), this, SLOT(checkD()));
	connect(ui.LE_d_Value, SIGNAL(editingFinished()), this, SLOT(checkd()));
	connect(ui.LE_Free_length_Value, SIGNAL(editingFinished()), this, SLOT(checkL()));
	//connect(ui.LE_Hs, SIGNAL(editingFinished()), this, SLOT(checkHs()));
	connect(ui.LE_inst_length, SIGNAL(editingFinished()), this, SLOT(checkInstLen()));
	connect(ui.LE_stroke, SIGNAL(editingFinished()), this, SLOT(checkStroke()));
	connect(ui.LE_N_lower, SIGNAL(editingFinished()), this, SLOT(checkNLower()));
	connect(ui.LE_N_upper, SIGNAL(editingFinished()), this, SLOT(checkNUpper()));
	connect(ui.LE_D_lower, SIGNAL(editingFinished()), this, SLOT(checkDLower()));
	connect(ui.LE_D_upper, SIGNAL(editingFinished()), this, SLOT(checkDUpper()));
	connect(ui.LE_d_lower, SIGNAL(editingFinished()), this, SLOT(checkdLower()));
	connect(ui.LE_d_upper, SIGNAL(editingFinished()), this, SLOT(checkdUpper()));
	connect(ui.LE_L_lower, SIGNAL(editingFinished()), this, SLOT(checkLLower()));
	connect(ui.LE_L_upper, SIGNAL(editingFinished()), this, SLOT(checkLUpper()));
	connect(ui.LE_N_delta, SIGNAL(editingFinished()), this, SLOT(checkNdelta()));
	connect(ui.LE_D_delta, SIGNAL(editingFinished()), this, SLOT(checkDdelta()));
	connect(ui.LE_d_delta, SIGNAL(editingFinished()), this, SLOT(checkddelta()));
	connect(ui.LE_L_delta, SIGNAL(editingFinished()), this, SLOT(checkLdelta()));
	connect(ui.LE_density, SIGNAL(editingFinished()), this, SLOT(checkDensity()));
	connect(ui.LE_shear_modulus, SIGNAL(editingFinished()), this, SLOT(checkShearModulus()));
	connect(ui.LE_eq_mass, SIGNAL(editingFinished()), this, SLOT(checkEqMass()));
	connect(ui.LE_Max_Stress, SIGNAL(editingFinished()), this, SLOT(checkMaxStress()));
	//connect(ui.LE_Max_Stress_maximum, SIGNAL(editingFinished()), this, SLOT(checkMSMax()));
	//connect(ui.LE_Stiffness_minimum, SIGNAL(editingFinished()), this, SLOT(checkLSMin()));
	//connect(ui.LE_Stiffness_maximum, SIGNAL(editingFinished()), this, SLOT(checkLSMax()));
	connect(ui.LE_BH_rate, SIGNAL(editingFinished()), this, SLOT(checkBHRate()));
	connect(ui.LE_BH_stress_const, SIGNAL(editingFinished()), this, SLOT(checkBHSc()));
	//connect(ui.LE_Mass_const, SIGNAL(editingFinished()), this, SLOT(checkMc()));
	connect(ui.LE_Min_Spring_index_const, SIGNAL(editingFinished()), this, SLOT(checkMinSIc()));
	connect(ui.LE_Max_Spring_index_const, SIGNAL(editingFinished()), this, SLOT(checkMaxSIc()));
	connect(ui.LE_aspect_ratio_const, SIGNAL(editingFinished()), this, SLOT(checkARc()));
	//connect(ui.LE_Weight_const, SIGNAL(editingFinished()), this, SLOT(checkWc()));
	connect(ui.LE_Potential_const, SIGNAL(editingFinished()), this, SLOT(checkPc()));
	
	connect(&dhs, SIGNAL(mySignal(int)), this, SLOT(mySlot(int)));
	//ui.progressBar->setMaximum(100000);
	ui.progressBar->setValue(0);
	//ui.LE_Li_delta->setText("1");
	QFile file("autoSave.dat");
	if (file.open(QIODevice::ReadOnly))
	{
		QString str;
		file.read((char*)&dhs.N, sizeof(double) * 39);
		QTextStream(&str) << dhs.N; ui.LE_N_value->setText(str);	str.clear();
		QTextStream(&str) << dhs.D; ui.LE_D_Value->setText(str); str.clear();
		QTextStream(&str) << dhs.d; ui.LE_d_Value->setText(str); str.clear();
		QTextStream(&str) << dhs.FreeLength; ui.LE_Free_length_Value->setText(str); str.clear();
		QTextStream(&str) << dhs.InstallLength; ui.LE_inst_length->setText(str); str.clear();
		QTextStream(&str) << dhs.Stroke; ui.LE_stroke->setText(str); str.clear();
		//QTextStream(&str) << dhs.DisBH; ui.LE_Hs->setText(str); str.clear();
		QTextStream(&str) << dhs.NLower; ui.LE_N_lower->setText(str); str.clear();
		QTextStream(&str) << dhs.NUpper; ui.LE_N_upper->setText(str); str.clear();
		QTextStream(&str) << dhs.DLower; ui.LE_D_lower->setText(str); str.clear();
		QTextStream(&str) << dhs.DUpper; ui.LE_D_upper->setText(str); str.clear();
		QTextStream(&str) << dhs.dLower; ui.LE_d_lower->setText(str); str.clear();
		QTextStream(&str) << dhs.dUpper; ui.LE_d_upper->setText(str); str.clear();
		QTextStream(&str) << dhs.FreeLengthLower; ui.LE_L_lower->setText(str); str.clear();
		QTextStream(&str) << dhs.FreeLengthUpper; ui.LE_L_upper->setText(str); str.clear();
		QTextStream(&str) << dhs.deltaN; ui.LE_N_delta->setText(str); str.clear();
		QTextStream(&str) << dhs.deltaD; ui.LE_D_delta->setText(str); str.clear();
		QTextStream(&str) << dhs.deltad; ui.LE_d_delta->setText(str); str.clear();
		QTextStream(&str) << dhs.deltaFreeLength; ui.LE_L_delta->setText(str); str.clear();
		QTextStream(&str) << dhs.density; ui.LE_density->setText(str); str.clear();
		QTextStream(&str) << dhs.eq_mass; ui.LE_eq_mass->setText(str); str.clear();
		QTextStream(&str) << dhs.shearModulus; ui.LE_shear_modulus->setText(str); str.clear();
		QTextStream(&str) << dhs.PreComp; ui.LE_pre_comp->setText(str); str.clear();
		QTextStream(&str) << dhs.TotalComp; ui.LE_total_comp->setText(str); str.clear();
		QTextStream(&str) << dhs.BHLimit; ui.LE_block_height->setText(str); str.clear();
		QTextStream(&str) << dhs.cMaxStress; ui.LE_Max_Stress->setText(str); str.clear();
		QTextStream(&str) << dhs.DisBH; ui.LE_BH_rate->setText(str); str.clear();
		//QTextStream(&str) << dhs.cMinStress; ui.LE_Max_Stress_minimum->setText(str); str.clear();
		//QTextStream(&str) << dhs.cMaxStiffness; ui.LE_Stiffness_maximum->setText(str); str.clear();
		//QTextStream(&str) << dhs.cMinStiffness; ui.LE_Stiffness_minimum->setText(str); str.clear();
		QTextStream(&str) << dhs.cBHStress; ui.LE_BH_stress_const->setText(str); str.clear();
		//QTextStream(&str) << dhs.cMass; ui.LE_Mass_const->setText(str); str.clear();
		QTextStream(&str) << dhs.cMaxSpringIndex; ui.LE_Max_Spring_index_const->setText(str); str.clear();
		QTextStream(&str) << dhs.cMinSpringIndex; ui.LE_Min_Spring_index_const->setText(str); str.clear();
		QTextStream(&str) << dhs.cAspectRatio; ui.LE_aspect_ratio_const->setText(str); str.clear();
		//QTextStream(&str) << dhs.cWeight; ui.LE_Weight_const->setText(str); str.clear();
		QTextStream(&str) << dhs.cPotential; ui.LE_Potential_const->setText(str); str.clear(); 
	}
	setInerOuterDiameter();
	file.close();

	newAct = new QAction(QIcon(":/DHSpring/new.png"), tr("&New"), this);
	newAct->setStatusTip(tr("New"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(newproj()));

	openAct = new QAction(QIcon(":/DHSpring/open.png"), tr("&Open"), this);
	openAct->setStatusTip(tr("Open input & output data"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openproj()));

	saveAct = new QAction(QIcon(":/DHSpring/save.png"), tr("&Save"), this);
	saveAct->setStatusTip(tr("Save input & output"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveproj()));

	ui.inputToolbar->addAction(newAct);
	ui.inputToolbar->addAction(openAct);
	ui.inputToolbar->addAction(saveAct);
	connect(ui.TB_ZoomSpringImage, SIGNAL(clicked()), this, SLOT(actionZoomSpringImage()));
	//QLabel* imageLabel = new QLabel;
	//imageLabel->setBackgroundRole(QPalette::Base);
	//imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	//imageLabel->setScaledContents(true);
	//ui.SA_spring_pic->setBackgroundRole(QPalette::Dark);
	//
	//QImage image(":/ DHSpring / measure_coil_spring.jpg");
	//imageLabel->setPixmap(QPixmap::fromImage(image));
	//ui.SA_spring_pic->setWidget(imageLabel);
}

DHSpring::~DHSpring()
{
	if (rTable) delete rTable; rTable = NULL;
	if (springImageDialog) delete springImageDialog; springImageDialog = NULL;
}

void DHSpring::newproj()
{
	dhs.reset();
	if(rTable)
		rTable->reset();
	ui.LE_N_value->setText("0");
	ui.LE_D_Value->setText("0"); 
	ui.LE_d_Value->setText("0"); 
	ui.LE_Free_length_Value->setText("0"); 
	ui.LE_inst_length->setText("0"); 
	ui.LE_stroke->setText("0"); 
	//ui.LE_Hs->setText("0"); 
	ui.LE_N_lower->setText("0"); 
	ui.LE_N_upper->setText("0"); 
	ui.LE_D_lower->setText("0"); 
	ui.LE_D_upper->setText("0"); 
	ui.LE_d_lower->setText("0"); 
	ui.LE_d_upper->setText("0"); 
	ui.LE_L_lower->setText("0"); 
	ui.LE_L_upper->setText("0"); 
	ui.LE_N_delta->setText("0"); 
	ui.LE_D_delta->setText("0"); 
	ui.LE_d_delta->setText("0");
	ui.LE_L_delta->setText("0"); 
//	ui.LE_Li_delta->setText("1"); 
	ui.LE_density->setText("0"); 
	ui.LE_eq_mass->setText("0"); 
	ui.LE_shear_modulus->setText("0"); 
	ui.LE_pre_comp->setText("0"); 
	ui.LE_total_comp->setText("0"); 
	ui.LE_Max_Stress->setText("0");
	ui.LE_BH_rate->setText("0");
	ui.LE_Max_Stress->setText("0");
	//ui.LE_Stiffness_minimum->setText("0");
	//ui.LE_Stiffness_maximum->setText("0");
	ui.LE_Min_Spring_index_const->setText("0");
	ui.LE_Max_Spring_index_const->setText("0");
	ui.LE_BH_stress_const->setText("0");
	//ui.LE_Mass_const->setText("0");
	ui.LE_aspect_ratio_const->setText("0");
	//ui.LE_Weight_const->setText("0");;
	ui.LE_Potential_const->setText("0");
	ui.LE_block_height->setText("0");
}

void DHSpring::openproj()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("open"), recentlyPath, tr("Text File (*.txt)"));
	if (filename.isEmpty())
		return;
	QFile file(filename);
	QString str;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)); {
		QTextStream in(&file);
		dhs.reset();
		while (str != "end"){
			in >> str;
			if (str == kor("��ȿ�Ǽ�")) { in >> str >> str; dhs.N = str.toDouble(); }
			else if (str == kor("�߽ɰ�")) { in >> str >> str; dhs.D = str.toDouble(); }
			else if (str == kor("������")) { in >> str >> str; dhs.d = str.toDouble(); }
			else if (str == kor("������")) { in >> str >> str; dhs.FreeLength = str.toDouble(); }
			else if (str == kor("������")) { in >> str >> str; dhs.DisBH = str.toDouble(); }
			else if (str == kor("��������")) { in >> str >> str; dhs.InstallLength = str.toDouble(); }
			else if (str == kor("��Ʈ��ũ")) { in >> str >> str; dhs.Stroke = str.toDouble(); }
			else if (str == kor("�ʱ���෮")) { in >> str >> str; dhs.PreComp = str.toDouble(); }
			else if (str == kor("�ִ���෮")) { in >> str >> str; dhs.TotalComp = str.toDouble(); }
			else if (str == kor("������")) { in >> str >> str; dhs.BHLimit = str.toDouble(); }
			else if (str == kor("��ȿ�Ǽ�(����)")) { in >> str >> str; dhs.NLower = str.toDouble(); }
			else if (str == kor("��ȿ�Ǽ�(����)")) { in >> str >> str; dhs.NUpper = str.toDouble(); }
			else if (str == kor("��ȿ�Ǽ�(����)")) { in >> str >> str; dhs.deltaN = str.toDouble(); }
			else if (str == kor("�߽ɰ�(����)")) { in >> str >> str; dhs.DLower = str.toDouble(); }
			else if (str == kor("�߽ɰ�(����)")) { in >> str >> str; dhs.DUpper = str.toDouble(); }
			else if (str == kor("�߽ɰ�(����)")) { in >> str >> str; dhs.deltaD = str.toDouble(); }
			else if (str == kor("������(����)")) { in >> str >> str; dhs.dLower = str.toDouble(); }
			else if (str == kor("������(����)")) { in >> str >> str; dhs.dUpper = str.toDouble(); }
			else if (str == kor("������(����)")) { in >> str >> str; dhs.deltad = str.toDouble(); }
			else if (str == kor("������(����)")) { in >> str >> str; dhs.FreeLengthLower = str.toDouble(); }
			else if (str == kor("������(����)")) { in >> str >> str; dhs.FreeLengthUpper = str.toDouble(); }
			else if (str == kor("������(����)")) { in >> str >> str; dhs.deltaFreeLength = str.toDouble(); }
			else if (str == kor("�е�")) { in >> str >> str; dhs.density = str.toDouble(); }
			else if (str == kor("����ź����")) { in >> str >> str; dhs.shearModulus = str.toDouble(); }
			else if (str == kor("�����")) { in >> str >> str; dhs.eq_mass = str.toDouble(); }
			//else if (str == kor("�ð�����")) { in >> str >> str; dhs.dt = str.toDouble(); }
			//else if (str == kor("�ؼ��ð�")) { in >> str >> str; dhs.et = str.toDouble(); }
			//else if (str == kor("�ִ�����(���ѱ���)")) { in >> str >> str; dhs.cMinStress = str.toDouble(); }
			else if (str == kor("�ִ�����(���ѱ���)")) { in >> str >> str; dhs.cMaxStress = str.toDouble(); }
			//else if (str == kor("����(���ѱ���)")) { in >> str >> str; dhs.cMinStiffness = str.toDouble(); }
			//else if (str == kor("����(���ѱ���)")) { in >> str >> str; dhs.cMaxStiffness = str.toDouble(); }
			else if (str == kor("����������(���ѱ���)")) { in >> str >> str; dhs.cMinSpringIndex = str.toDouble(); }
			else if (str == kor("����������(���ѱ���)")) { in >> str >> str; dhs.cMaxSpringIndex = str.toDouble(); }
			else if (str == kor("����������")) { in >> str >> str; dhs.DisBH = str.toDouble(); }
			else if (str == kor("���������±���")) { in >> str >> str; dhs.cBHStress = str.toDouble(); }
			//else if (str == kor("��������")) { in >> str >> str; dhs.cMass = str.toDouble(); }
			else if (str == kor("��Ⱦ�񱸼�")) { in >> str >> str; dhs.cAspectRatio = str.toDouble(); }
			//else if (str == kor("���߱���")) { in >> str >> str; dhs.cWeight = str.toDouble(); }
			else if (str == kor("��ȿ���ټȱ���")) { in >> str >> str; dhs.cPotential = str.toDouble(); }

			if (str == "begin")
			{
				QString strList[18];
				for (unsigned int i = 0; i < 18; i++){
					in >> strList[i];
				}

				while (1){
					for (unsigned int i = 0; i < 18; i++){
						in >> strList[i];
					}
					if (strList[0] == "end")
					{
						str = strList[0];
						break;
					}					

					resultSet result = {
						strList[1].toDouble(),
						strList[2].toDouble(),
						strList[3].toDouble(),
						strList[4].toDouble(),
						strList[5].toDouble(),
						strList[6].toDouble(),
						strList[7].toDouble(),
						strList[8].toDouble(),
						strList[9].toDouble(),
						strList[10].toDouble(),
						strList[11].toDouble(),
						strList[12].toDouble(),
						strList[13].toDouble(),
						strList[14].toDouble(),
						strList[15].toDouble(),
						strList[16].toDouble(),
						strList[17].toDouble()
					};
					strList[0] == "0" ? dhs.ref_result = result : dhs.results.push(result);
				}
			}
		}
		
	}
	if (dhs.results.sizes())
		dhs.results.adjustment();
	str.clear();
	QTextStream(&str) << dhs.N; ui.LE_N_value->setText(str); str.clear();
	QTextStream(&str) << dhs.D; ui.LE_D_Value->setText(str); str.clear();
	QTextStream(&str) << dhs.d; ui.LE_d_Value->setText(str); str.clear();
	QTextStream(&str) << dhs.FreeLength; ui.LE_Free_length_Value->setText(str); str.clear();
	QTextStream(&str) << dhs.InstallLength; ui.LE_inst_length->setText(str); str.clear();
	QTextStream(&str) << dhs.Stroke; ui.LE_stroke->setText(str); str.clear();
	//QTextStream(&str) << dhs.DisBH; ui.LE_Hs->setText(str); str.clear();
	QTextStream(&str) << dhs.NLower; ui.LE_N_lower->setText(str); str.clear();
	QTextStream(&str) << dhs.NUpper; ui.LE_N_upper->setText(str); str.clear();
	QTextStream(&str) << dhs.DLower; ui.LE_D_lower->setText(str); str.clear();
	QTextStream(&str) << dhs.DUpper; ui.LE_D_upper->setText(str); str.clear();
	QTextStream(&str) << dhs.dLower; ui.LE_d_lower->setText(str); str.clear();
	QTextStream(&str) << dhs.dUpper; ui.LE_d_upper->setText(str); str.clear();
	QTextStream(&str) << dhs.FreeLengthLower; ui.LE_L_lower->setText(str); str.clear();
	QTextStream(&str) << dhs.FreeLengthUpper; ui.LE_L_upper->setText(str); str.clear();
	QTextStream(&str) << dhs.deltaN; ui.LE_N_delta->setText(str); str.clear();
	QTextStream(&str) << dhs.deltaD; ui.LE_D_delta->setText(str); str.clear();
	QTextStream(&str) << dhs.deltad; ui.LE_d_delta->setText(str); str.clear();
	QTextStream(&str) << dhs.deltaFreeLength; ui.LE_L_delta->setText(str); str.clear();
	QTextStream(&str) << dhs.density; ui.LE_density->setText(str); str.clear();
	QTextStream(&str) << dhs.eq_mass; ui.LE_eq_mass->setText(str); str.clear();
	QTextStream(&str) << dhs.shearModulus; ui.LE_shear_modulus->setText(str); str.clear();
	QTextStream(&str) << dhs.PreComp; ui.LE_pre_comp->setText(str); str.clear();
	QTextStream(&str) << dhs.TotalComp; ui.LE_total_comp->setText(str); str.clear();
	QTextStream(&str) << dhs.BHLimit; ui.LE_block_height->setText(str); str.clear();
	QTextStream(&str) << dhs.cMaxStress; ui.LE_Max_Stress->setText(str); str.clear();
	QTextStream(&str) << dhs.DisBH; ui.LE_BH_rate->setText(str); str.clear();
	//QTextStream(&str) << dhs.cMinStress; ui.LE_Max_Stress_minimum->setText(str); str.clear();
	//QTextStream(&str) << dhs.cMaxStiffness; ui.LE_Stiffness_maximum->setText(str); str.clear();
	//QTextStream(&str) << dhs.cMinStiffness; ui.LE_Stiffness_minimum->setText(str); str.clear();
	QTextStream(&str) << dhs.cBHStress; ui.LE_BH_stress_const->setText(str); str.clear();
	//QTextStream(&str) << dhs.cMass; ui.LE_Mass_const->setText(str); str.clear();
	QTextStream(&str) << dhs.cMaxSpringIndex; ui.LE_Max_Spring_index_const->setText(str); str.clear();
	QTextStream(&str) << dhs.cMinSpringIndex; ui.LE_Min_Spring_index_const->setText(str); str.clear();
	QTextStream(&str) << dhs.cAspectRatio; ui.LE_aspect_ratio_const->setText(str); str.clear();
	//QTextStream(&str) << dhs.cWeight; ui.LE_Weight_const->setText(str); str.clear();
	QTextStream(&str) << dhs.cPotential; ui.LE_Potential_const->setText(str); str.clear();
	setInerOuterDiameter();
}

void DHSpring::saveproj()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("save"), recentlyPath, tr("Text File (*.txt)"));
	if (filename.isEmpty())

		return;
	QFile file(filename);
	
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
		QTextStream out(&file);
		out << "// Input Data" << "\n";
		out << kor("��ȿ�Ǽ�                     : ") << ui.LE_N_value->text() << "\n";
		out << kor("�߽ɰ�                       : ") << ui.LE_D_Value->text() << "\n";
		out << kor("������                       : ") << ui.LE_d_Value->text() << "\n";
		out << kor("������                       : ") << ui.LE_Free_length_Value->text() << "\n";
		//out << kor("������                       : ") << ui.LE_Hs->text() << "\n";
		out << kor("��������                     : ") << ui.LE_inst_length->text() << "\n";
		out << kor("��Ʈ��ũ                     : ") << ui.LE_stroke->text() << "\n";
		out << kor("�ʱ���෮                   : ") << ui.LE_pre_comp->text() << "\n";
		out << kor("�ִ���෮                   : ") << ui.LE_total_comp->text() << "\n";
		out << kor("������                       : ") << ui.LE_block_height->text() << "\n";
		out << kor("��ȿ�Ǽ�(����)               : ") << ui.LE_N_lower->text() << "\n";
		out << kor("��ȿ�Ǽ�(����)               : ") << ui.LE_N_upper->text() << "\n";
		out << kor("��ȿ�Ǽ�(����)               : ") << ui.LE_N_delta->text() << "\n";
		out << kor("�߽ɰ�(����)                 : ") << ui.LE_D_lower->text() << "\n";
		out << kor("�߽ɰ�(����)                 : ") << ui.LE_D_upper->text() << "\n";
		out << kor("�߽ɰ�(����)                 : ") << ui.LE_D_delta->text() << "\n";
		out << kor("������(����)                 : ") << ui.LE_d_lower->text() << "\n";
		out << kor("������(����)                 : ") << ui.LE_d_upper->text() << "\n";
		out << kor("������(����)                 : ") << ui.LE_d_delta->text() << "\n";
		out << kor("������(����)                 : ") << ui.LE_L_lower->text() << "\n";
		out << kor("������(����)                 : ") << ui.LE_L_upper->text() << "\n";
		out << kor("������(����)                 : ") << ui.LE_L_delta->text() << "\n";
		out << kor("�е�                         : ") << ui.LE_density->text() << "\n";
		out << kor("����ź����                   : ") << ui.LE_shear_modulus->text() << "\n";
		out << kor("�����                     : ") << ui.LE_eq_mass->text() << "\n";
		//out << kor("�ð�����                     : ") << ui.LE_timestep->text() << "\n";
		//out << kor("�ؼ��ð�                     : ") << ui.LE_endtime->text() << "\n";
		out << kor("�ִ�����(���ѱ���)           : ") << ui.LE_Max_Stress->text() << "\n";
		//out << kor("�ִ�����(���ѱ���)           : ") << ui.LE_Max_Stress_maximum->text() << "\n";
		out << kor("����������(���ѱ���)         : ") << ui.LE_Min_Spring_index_const->text() << "\n";
		out << kor("����������(���ѱ���)         : ") << ui.LE_Max_Spring_index_const->text() << "\n";
		out << kor("����������					 : ") << ui.LE_BH_rate->text() << "\n";
		//out << kor("����(���ѱ���)               : ") << ui.LE_Stiffness_maximum->text() << "\n";
		out << kor("���������±���               : ") << ui.LE_BH_stress_const->text() << "\n";
		//out << kor("��������                     : ") << ui.LE_Mass_const->text() << "\n";
		out << kor("��Ⱦ�񱸼�                   : ") << ui.LE_aspect_ratio_const->text() << "\n";
		//out << kor("���߱���                     : ") << ui.LE_Weight_const->text() << "\n";
		out << kor("��ȿ���ټȱ���               : ") << ui.LE_Potential_const->text() << "\n";
		

		out << "\n" << "// Output Data" << "\n";
		out << "\n" << "begin" << "\n";
		out << kor("���̵� ") << kor("��ȿ�Ǽ� ") << kor("�߽ɰ� ") << kor("������ ") << kor("������ ") << kor("���� ") << kor("���� ") << kor("������ ") << kor("���� ") << kor("���������� ") << kor("�ִ����� ") << kor("���������� ") << kor("��ȿ���ټ� ") << kor("ȿ�� ") << kor("���޿����� ") << kor("���ܼӵ� ") << kor("���������� ") << kor("��Ⱦ�� ") << "\n";
		out << 0 << " " << dhs.ref_result.N << " " << dhs.ref_result.D << " " << dhs.ref_result.d << " " << dhs.ref_result.FreeLength << " " << dhs.ref_result.k << " " << dhs.ref_result.Mass << " " << dhs.ref_result.B_Height << " " << dhs.ref_result.P << " " << dhs.ref_result.P_BH << " " << dhs.ref_result.Sc << " " << dhs.ref_result.Sc_BH << " " << dhs.ref_result.PE_act << " " << dhs.ref_result.Efficiency << " " << dhs.ref_result.transferEnergy << " " << dhs.ref_result.v_ep << " " << dhs.ref_result.C << " " << dhs.ref_result.AR << " " << "\n";
		for (unsigned int i = 0; i < dhs.results.sizes(); i++){
 			resultSet result = dhs.results(i);
			out << i + 1 << " " << result.N << " " << result.D << " " << result.d << " " << result.FreeLength << " " << result.k <<" " << result.Mass << " " << result.B_Height << " " << result.P << " " << result.P_BH << " " << result.Sc << " " << result.Sc_BH << " " << result.PE_act << " " << result.Efficiency << " " << result.transferEnergy << " " << result.v_ep << " " << result.C << " " << result.AR << " " << "\n";
		}
		out << "end" << "\n";
	}
	file.close();
	recentlyPath = filename;
}

void DHSpring::actionAnalyze()
{	
	dhs.reset();
	dhs.N = ui.LE_N_value->text().toDouble();
	dhs.D = ui.LE_D_Value->text().toDouble();
	dhs.d = ui.LE_d_Value->text().toDouble();
	dhs.FreeLength = ui.LE_Free_length_Value->text().toDouble();
	//dhs.DisBH = ui.LE_Hs->text().toDouble();
	dhs.InstallLength = ui.LE_inst_length->text().toDouble();
	dhs.Stroke = ui.LE_stroke->text().toDouble();
	dhs.NLower = ui.LE_N_lower->text().toDouble();
	dhs.NUpper = ui.LE_N_upper->text().toDouble();
	dhs.deltaN = ui.LE_N_delta->text().toDouble();
	dhs.DLower = ui.LE_D_lower->text().toDouble();
	dhs.DUpper = ui.LE_D_upper->text().toDouble();
	dhs.deltaD = ui.LE_D_delta->text().toDouble();
	dhs.dLower = ui.LE_d_lower->text().toDouble();
	dhs.dUpper = ui.LE_d_upper->text().toDouble();
	dhs.deltad = ui.LE_d_delta->text().toDouble();
	dhs.FreeLengthLower = ui.LE_L_lower->text().toDouble();
	dhs.FreeLengthUpper = ui.LE_L_upper->text().toDouble();
	dhs.deltaFreeLength = ui.LE_L_delta->text().toDouble();
	dhs.density = ui.LE_density->text().toDouble();
	dhs.shearModulus = ui.LE_shear_modulus->text().toDouble();
	dhs.eq_mass = ui.LE_eq_mass->text().toDouble();
	dhs.DisBH = ui.LE_BH_rate->text().toDouble();
	dhs.cMaxStress = ui.LE_Max_Stress->text().toDouble();
	//dhs.cMinStress = ui.LE_Max_Stress_minimum->text().toDouble();
	//dhs.cMaxStiffness = ui.LE_Stiffness_maximum->text().toDouble();
	//dhs.cMinStiffness = ui.LE_Stiffness_minimum->text().toDouble();
	dhs.cBHStress = ui.LE_BH_stress_const->text().toDouble();
	//dhs.cMass = ui.LE_Mass_const->text().toDouble();
	dhs.cMinSpringIndex = ui.LE_Min_Spring_index_const->text().toDouble();
	dhs.cMaxSpringIndex = ui.LE_Max_Spring_index_const->text().toDouble();
	dhs.cAspectRatio = ui.LE_aspect_ratio_const->text().toDouble();
	//dhs.cWeight = ui.LE_Weight_const->text().toDouble();
	dhs.cPotential = ui.LE_Potential_const->text().toDouble();

	ui.progressBar->setValue(0);
	//dhs.setTestExample();
	if (!dhs.initialize()){
		return;
	}
	int max = (int)dhs.totalIteration();
	ui.progressBar->setMaximum(max);
	dhs.solve();
	
	//dhs.
}

void DHSpring::actionZoomSpringImage()
{
	if (!springImageDialog){
		springImageDialog = new ZoomSpringImageDialog;
	}
	springImageDialog->f_length = ui.LE_Free_length_Value->text().toDouble();
	springImageDialog->equip_length = ui.LE_inst_length->text().toDouble();
	springImageDialog->init_comp = ui.LE_pre_comp->text().toDouble();
	springImageDialog->d = ui.LE_d_Value->text().toDouble();
	springImageDialog->stroke = ui.LE_stroke->text().toDouble();
	springImageDialog->max_comp = ui.LE_total_comp->text().toDouble();
	springImageDialog->inner_diameter = ui.LE_Iner_Diameter->text().toDouble();
	springImageDialog->outer_diameter = ui.LE_Outer_Diameter->text().toDouble();
	springImageDialog->middle_diameter = ui.LE_D_Value->text().toDouble();
	springImageDialog->setValue();
	springImageDialog->show();
}

void DHSpring::actionResultTable()
{
	if (!rTable){
		rTable = new resultTable;
	}

	if (dhs.isExistResultData()){
		rTable->setTable(dhs.ref_result, dhs.results);
	}
	rTable->show();
}

void DHSpring::setInerOuterDiameter()
{
	if (ui.LE_D_Value->text() == "" || ui.LE_D_Value->text() == "0"){
		return;
	}
	if (ui.LE_d_Value->text() == "" || ui.LE_d_Value->text() == "0"){
		return;
	}

	double D = ui.LE_D_Value->text().toDouble();
	double d = ui.LE_d_Value->text().toDouble();

	QString str;
	QTextStream(&str) << D - d;
	ui.LE_Iner_Diameter->setText(str);
	str.clear();
	QTextStream(&str) << D + d;
	ui.LE_Outer_Diameter->setText(str);
}

void DHSpring::setInitCompression()
{
	QString str;
	double fLen = ui.LE_Free_length_Value->text().toDouble();
	double iLen = ui.LE_inst_length->text().toDouble();
	QTextStream(&str) << fLen - iLen;
	ui.LE_pre_comp->setText(str);
	
}

void DHSpring::setTotalCompression()
{
	QString str;
	double pComp = ui.LE_pre_comp->text().toDouble();
	double stroke = ui.LE_stroke->text().toDouble();
	double maxComp = pComp + stroke;
	QTextStream(&str) << maxComp;
	setBHLimit();
	double flen = ui.LE_Free_length_Value->text().toDouble();
	double bh = ui.LE_block_height->text().toDouble();
	ui.LE_total_comp->setText(str);
	if((flen - maxComp) <= bh){		
		showMessageBox(kor("�ִ� ����� ���̰� ������ �ʰ��Ͽ��� �մϴ�."), QMessageBox::Critical);
	}
}

void DHSpring::setBHLimit()
{
	if (ui.LE_N_value->text() == "" || ui.LE_N_value->text() == "0"){
		return;
	}
	if (ui.LE_d_Value->text() == "" || ui.LE_d_Value->text() == "0"){
		return;
	}
	double _N = ui.LE_N_value->text().toDouble();
	double _d = ui.LE_d_Value->text().toDouble();
	//double dBH = ui.LE_Hs->text().toDouble();

	QString str;
	QTextStream(&str) << (_N + 1.6) * _d;
	ui.LE_block_height->setText(str);
}

bool DHSpring::checkNumericData(QString data)
{
	for (QString::iterator it = data.begin(); it != data.end(); it++){
		QChar *ch = it;
		if (!((*ch >= 48 && *ch <= 57) || *ch == 46 || *ch == 45 || *ch == 101))
		{
			return false;
		}
	}
	return true;
}

void DHSpring::showMessageBox(QString data, QMessageBox::Icon ic)
{
	QMessageBox msgBox;
	msgBox.setText(tr(data.toStdString().c_str()));
	msgBox.setIcon(ic);
	msgBox.exec();
}

void DHSpring::mySlot(int val)
{
	ui.progressBar->setValue(val);
	/*QTextStream(&messageString) << qSetFieldWidth(10) << left << kor("���̵� : ") << dhs.success_count << ", " << kor("���ܼӵ� : ") << dhs.v_ep << "\n";
	ui.messageWindow->clear();
	ui.messageWindow->setText(messageString);*/
	//ui.progressBar->set
}