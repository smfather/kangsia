#ifndef PARVIEW_H
#define PARVIEW_H

#include <QtWidgets/QMainWindow>
#include "ui_parview.h"
#include "particleInfoDialog.h"
#include "glwidget.h"
#include "DEM/DemSimulation.h"

class QLabel;

namespace parview
{
	class parVIEW : public QMainWindow
	{
		Q_OBJECT

	public:
		parVIEW(QWidget *parent = 0);
		~parVIEW();

		private slots:
		void ChangeShape();
		void ChangeComboBox(int);
		void mySlot();
		void newproj();
		void openproj();
		void openrtproj();
		void saveproj();
		void ani_previous2x();
		void ani_previous1x();
		void ani_play();
		void ani_pause();
		void ani_forward1x();
		void ani_forward2x();
		void ani_scrollbar();
		void makeCube();
		void makeParticle();
		void solveProcess();

		void openPinfoDialog();

	private:
		GLWidget *gl;
		particleInfoDialog *pinfoDialog;
		Ui::parVIEW ui;
		bool animation_statement;
		

		QString previous_directory;

		//QAction *MenuChangeShapeAct;
		QAction *newAct;
		QAction *openAct;
		QAction *openRtAct;
		QAction *saveAct;
		QAction *aniPlayAct;
		QAction *aniPauseAct;
		QAction *aniPreviousAct;
		QAction *aniPreviousAct2;
		QAction *aniForwardAct;
		QAction *aniForwardAct2;
		QAction *makeCubeAct;
		QAction *makeParticleAct;
		QAction *solveProcessAct;

		QAction *pinfoAct;

		QSlider *HSlider;
		QSlider *PHSlider;
		QLineEdit *LEframe;
		QLineEdit *LETimes;
		QLineEdit *LEparticleID;
		QLabel *Lframe;
		QLabel *LparticleID;
		QComboBox *viewObjectComboBox;

		DemSimulation *dem;
	};
}

#endif // PARVIEW_H
