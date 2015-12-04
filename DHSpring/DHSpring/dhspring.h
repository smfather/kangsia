#ifndef DHSPRING_H
#define DHSPRING_H

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_dhspring.h"
#include "dh_solver.h"
#include "ZoomSpringImageDialog.h"

class DHSpring : public QMainWindow
{
	Q_OBJECT

public:
	DHSpring(QWidget *parent = 0);
	~DHSpring();

	private slots:
	void newproj();
	void openproj();
	void saveproj();
	void actionZoomSpringImage();
	void actionAnalyze();
	void actionResultTable();
	void setInitCompression();
	void setInerOuterDiameter();
	void setTotalCompression();
	void setBHLimit();
	void mySlot(int);

	void checkN() { if (!checkNumericData(ui.LE_N_value->text())){ showMessageBox(kor("��ȿ���� ���� ��ȿ�Ǽ�(N) �������Դϴ�.")); } }
	void checkD() { if (!checkNumericData(ui.LE_D_Value->text())) { showMessageBox(kor("��ȿ���� ���� �߽ɰ�(D) �������Դϴ�.")); } }
	void checkd() { if (!checkNumericData(ui.LE_d_Value->text())) { showMessageBox(kor("��ȿ���� ���� ������(d) �������Դϴ�.")); } }
	void checkL() { if (!checkNumericData(ui.LE_Free_length_Value->text())) { showMessageBox(kor("��ȿ���� ���� ������(L) �������Դϴ�.")); } }
	//void checkHs() { if (!checkNumericData(ui.LE_Hs->text())) { showMessageBox(kor("��ȿ���� ���� ������(Hs) �������Դϴ�.")); } }
	void checkInstLen() { if (!checkNumericData(ui.LE_inst_length->text())) { showMessageBox(kor("��ȿ���� ���� �������� �������Դϴ�.")); } }
	void checkStroke()  { if (!checkNumericData(ui.LE_stroke->text())) { showMessageBox(kor("��ȿ���� ���� ��Ʈ��ũ �������Դϴ�.")); } }
	/*void checkInitComp()  { checkNumericData(ui.LE_N_value->text())) { showMessageBox(kor("��ȿ���� ���� ��ȿ�Ǽ�(N) �������Դϴ�.")); } }
	void checkTotalComp(){ checkNumericData(ui.LE_N_value->text())) { showMessageBox(kor("��ȿ���� ���� ��ȿ�Ǽ�(N) �������Դϴ�.")); } }
	void checkBHeight(){ checkNumericData(ui.LE_N_value->text())) { showMessageBox(kor("��ȿ���� ���� ��ȿ�Ǽ�(N) �������Դϴ�.")); } }*/
	void checkNLower(){ if (!checkNumericData(ui.LE_N_lower->text())) { showMessageBox(kor("��ȿ���� ���� ��ȿ�Ǽ�(N) ���� �������Դϴ�.")); } }
	void checkNUpper(){ if (!checkNumericData(ui.LE_N_upper->text())) { showMessageBox(kor("��ȿ���� ���� ��ȿ�Ǽ�(N) ���� �������Դϴ�.")); } }
	void checkDLower(){ if (!checkNumericData(ui.LE_D_lower->text())) { showMessageBox(kor("��ȿ���� ���� �߽ɰ�(D) ���� �������Դϴ�.")); } }
	void checkDUpper(){ if (!checkNumericData(ui.LE_D_upper->text())) { showMessageBox(kor("��ȿ���� ���� �߽ɰ�(D) ���� �������Դϴ�.")); } }
	void checkdLower(){ if (!checkNumericData(ui.LE_d_lower->text())) { showMessageBox(kor("��ȿ���� ���� ������(d) ���� �������Դϴ�.")); } }
	void checkdUpper(){ if (!checkNumericData(ui.LE_d_upper->text())) { showMessageBox(kor("��ȿ���� ���� ������(d) ���� �������Դϴ�.")); } }
	void checkLLower(){ if (!checkNumericData(ui.LE_L_lower->text())) { showMessageBox(kor("��ȿ���� ���� ������(L) ���� �������Դϴ�.")); } }
	void checkLUpper(){ if (!checkNumericData(ui.LE_L_upper->text())) { showMessageBox(kor("��ȿ���� ���� ������(L) ���� �������Դϴ�.")); } }
	void checkNdelta(){ if (!checkNumericData(ui.LE_N_delta->text())) { showMessageBox(kor("��ȿ���� ���� ��ȿ�Ǽ�(N) ���� �������Դϴ�.")); } }
	void checkDdelta(){ if (!checkNumericData(ui.LE_D_delta->text())) { showMessageBox(kor("��ȿ���� ���� �߽ɰ�(D) ���� �������Դϴ�.")); } }
	void checkddelta(){ if (!checkNumericData(ui.LE_d_delta->text())) { showMessageBox(kor("��ȿ���� ���� ������(d) ���� �������Դϴ�.")); } }
	void checkLdelta(){ if (!checkNumericData(ui.LE_L_delta->text())) { showMessageBox(kor("��ȿ���� ���� ������(L) ���� �������Դϴ�.")); } }
	void checkDensity(){ if (!checkNumericData(ui.LE_density->text())) { showMessageBox(kor("��ȿ���� ���� �е� �������Դϴ�.")); } }
	void checkShearModulus(){ if (!checkNumericData(ui.LE_shear_modulus->text())) { showMessageBox(kor("��ȿ���� ���� ���� ź���� �������Դϴ�.")); } }
	void checkEqMass(){ if (!checkNumericData(ui.LE_eq_mass->text())) { showMessageBox(kor("��ȿ���� ���� ����� �������Դϴ�.")); } }
	void checkMaxStress(){ if (!checkNumericData(ui.LE_Max_Stress->text())) { showMessageBox(kor("��ȿ���� ���� �ִ����� �ּ� �������� �������Դϴ�.")); } }
	void checkBHRate(){ if (!checkNumericData(ui.LE_BH_rate->text())) { showMessageBox(kor("��ȿ�ϱ� ���� ������ �������� ������ �Դϴ�.")); } }
	//void checkMSMax(){ if (!checkNumericData(ui.LE_Max_Stress_maximum->text())) { showMessageBox(kor("��ȿ���� ���� �ִ����� �ִ� �������� �������Դϴ�.")); } }
	//void checkLSMin(){ if (!checkNumericData(ui.LE_Stiffness_minimum->text())) { showMessageBox(kor("��ȿ���� ���� ���� �ּ� �������� �������Դϴ�.")); } }
	//void checkLSMax(){ if (!checkNumericData(ui.LE_Stiffness_maximum->text())) { showMessageBox(kor("��ȿ���� ���� ���� �ִ� �������� �������Դϴ�.")); } }
	void checkBHSc(){ if (!checkNumericData(ui.LE_BH_stress_const->text())) { showMessageBox(kor("��ȿ���� ���� ���������� �������� �������Դϴ�.")); } }
	//void checkMc(){ if (!checkNumericData(ui.LE_Mass_const->text())) { showMessageBox(kor("��ȿ���� ���� ���� �������� �������Դϴ�.")); } }
	void checkMinSIc(){ if (!checkNumericData(ui.LE_Min_Spring_index_const->text())) { showMessageBox(kor("��ȿ���� ���� �ּ� ���������� �������� �������Դϴ�.")); } }
	void checkMaxSIc(){ if (!checkNumericData(ui.LE_Max_Spring_index_const->text())) { showMessageBox(kor("��ȿ���� ���� �ִ� ���������� �������� �������Դϴ�.")); } }
	void checkARc(){ if (!checkNumericData(ui.LE_aspect_ratio_const->text())) { showMessageBox(kor("��ȿ���� ���� ��Ⱦ�� �������� �������Դϴ�.")); } }
	//void checkWc(){ if (!checkNumericData(ui.LE_Weight_const->text())) { showMessageBox(kor("��ȿ���� ���� ���� �������� �������Դϴ�.")); } }
	void checkPc(){ if (!checkNumericData(ui.LE_Potential_const->text())) { showMessageBox(kor("��ȿ���� ���� ��ȿ���ټ� �������� �������Դϴ�.")); } }

private:
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	bool checkNumericData(QString data);
	void showMessageBox(QString data, QMessageBox::Icon ic = QMessageBox::Critical);

	resultTable *rTable;
	ZoomSpringImageDialog *springImageDialog;
	dh_solver dhs;
	Ui::DHSpringClass ui;
	QString recentlyPath = "C:/";
	QString messageString;
};

#endif // DHSPRING_H
