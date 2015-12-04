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

	void checkN() { if (!checkNumericData(ui.LE_N_value->text())){ showMessageBox(kor("유효하지 않은 유효권수(N) 데이터입니다.")); } }
	void checkD() { if (!checkNumericData(ui.LE_D_Value->text())) { showMessageBox(kor("유효하지 않은 중심경(D) 데이터입니다.")); } }
	void checkd() { if (!checkNumericData(ui.LE_d_Value->text())) { showMessageBox(kor("유효하지 않은 재질경(d) 데이터입니다.")); } }
	void checkL() { if (!checkNumericData(ui.LE_Free_length_Value->text())) { showMessageBox(kor("유효하지 않은 자유장(L) 데이터입니다.")); } }
	//void checkHs() { if (!checkNumericData(ui.LE_Hs->text())) { showMessageBox(kor("유효하지 않은 밀착고(Hs) 데이터입니다.")); } }
	void checkInstLen() { if (!checkNumericData(ui.LE_inst_length->text())) { showMessageBox(kor("유효하지 않은 장착길이 데이터입니다.")); } }
	void checkStroke()  { if (!checkNumericData(ui.LE_stroke->text())) { showMessageBox(kor("유효하지 않은 스트로크 데이터입니다.")); } }
	/*void checkInitComp()  { checkNumericData(ui.LE_N_value->text())) { showMessageBox(kor("유효하지 않은 유효권수(N) 데이터입니다.")); } }
	void checkTotalComp(){ checkNumericData(ui.LE_N_value->text())) { showMessageBox(kor("유효하지 않은 유효권수(N) 데이터입니다.")); } }
	void checkBHeight(){ checkNumericData(ui.LE_N_value->text())) { showMessageBox(kor("유효하지 않은 유효권수(N) 데이터입니다.")); } }*/
	void checkNLower(){ if (!checkNumericData(ui.LE_N_lower->text())) { showMessageBox(kor("유효하지 않은 유효권수(N) 하한 데이터입니다.")); } }
	void checkNUpper(){ if (!checkNumericData(ui.LE_N_upper->text())) { showMessageBox(kor("유효하지 않은 유효권수(N) 상한 데이터입니다.")); } }
	void checkDLower(){ if (!checkNumericData(ui.LE_D_lower->text())) { showMessageBox(kor("유효하지 않은 중심경(D) 하한 데이터입니다.")); } }
	void checkDUpper(){ if (!checkNumericData(ui.LE_D_upper->text())) { showMessageBox(kor("유효하지 않은 중심경(D) 상한 데이터입니다.")); } }
	void checkdLower(){ if (!checkNumericData(ui.LE_d_lower->text())) { showMessageBox(kor("유효하지 않은 재질경(d) 하한 데이터입니다.")); } }
	void checkdUpper(){ if (!checkNumericData(ui.LE_d_upper->text())) { showMessageBox(kor("유효하지 않은 재질경(d) 상한 데이터입니다.")); } }
	void checkLLower(){ if (!checkNumericData(ui.LE_L_lower->text())) { showMessageBox(kor("유효하지 않은 자유장(L) 하한 데이터입니다.")); } }
	void checkLUpper(){ if (!checkNumericData(ui.LE_L_upper->text())) { showMessageBox(kor("유효하지 않은 자유장(L) 상한 데이터입니다.")); } }
	void checkNdelta(){ if (!checkNumericData(ui.LE_N_delta->text())) { showMessageBox(kor("유효하지 않은 유효권수(N) 증분 데이터입니다.")); } }
	void checkDdelta(){ if (!checkNumericData(ui.LE_D_delta->text())) { showMessageBox(kor("유효하지 않은 중심경(D) 증분 데이터입니다.")); } }
	void checkddelta(){ if (!checkNumericData(ui.LE_d_delta->text())) { showMessageBox(kor("유효하지 않은 재질경(d) 증분 데이터입니다.")); } }
	void checkLdelta(){ if (!checkNumericData(ui.LE_L_delta->text())) { showMessageBox(kor("유효하지 않은 자유장(L) 증분 데이터입니다.")); } }
	void checkDensity(){ if (!checkNumericData(ui.LE_density->text())) { showMessageBox(kor("유효하지 않은 밀도 데이터입니다.")); } }
	void checkShearModulus(){ if (!checkNumericData(ui.LE_shear_modulus->text())) { showMessageBox(kor("유효하지 않은 전단 탄성률 데이터입니다.")); } }
	void checkEqMass(){ if (!checkNumericData(ui.LE_eq_mass->text())) { showMessageBox(kor("유효하지 않은 등가질량 데이터입니다.")); } }
	void checkMaxStress(){ if (!checkNumericData(ui.LE_Max_Stress->text())) { showMessageBox(kor("유효하지 않은 최대응력 최소 구속조건 데이터입니다.")); } }
	void checkBHRate(){ if (!checkNumericData(ui.LE_BH_rate->text())) { showMessageBox(kor("유효하기 않은 밀착율 구속조건 데이터 입니다.")); } }
	//void checkMSMax(){ if (!checkNumericData(ui.LE_Max_Stress_maximum->text())) { showMessageBox(kor("유효하지 않은 최대응력 최대 구속조건 데이터입니다.")); } }
	//void checkLSMin(){ if (!checkNumericData(ui.LE_Stiffness_minimum->text())) { showMessageBox(kor("유효하지 않은 강성 최소 구속조건 데이터입니다.")); } }
	//void checkLSMax(){ if (!checkNumericData(ui.LE_Stiffness_maximum->text())) { showMessageBox(kor("유효하지 않은 강성 최대 구속조건 데이터입니다.")); } }
	void checkBHSc(){ if (!checkNumericData(ui.LE_BH_stress_const->text())) { showMessageBox(kor("유효하지 않은 밀착고응력 구속조건 데이터입니다.")); } }
	//void checkMc(){ if (!checkNumericData(ui.LE_Mass_const->text())) { showMessageBox(kor("유효하지 않은 질량 구속조건 데이터입니다.")); } }
	void checkMinSIc(){ if (!checkNumericData(ui.LE_Min_Spring_index_const->text())) { showMessageBox(kor("유효하지 않은 최소 스프링지수 구속조건 데이터입니다.")); } }
	void checkMaxSIc(){ if (!checkNumericData(ui.LE_Max_Spring_index_const->text())) { showMessageBox(kor("유효하지 않은 최대 스프링지수 구속조건 데이터입니다.")); } }
	void checkARc(){ if (!checkNumericData(ui.LE_aspect_ratio_const->text())) { showMessageBox(kor("유효하지 않은 종횡비 구속조건 데이터입니다.")); } }
	//void checkWc(){ if (!checkNumericData(ui.LE_Weight_const->text())) { showMessageBox(kor("유효하지 않은 하중 구속조건 데이터입니다.")); } }
	void checkPc(){ if (!checkNumericData(ui.LE_Potential_const->text())) { showMessageBox(kor("유효하지 않은 유효포텐셜 구속조건 데이터입니다.")); } }

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
