#ifndef SOLVEDIALOG_H
#define SOLVEDIALOG_H

#include <QDialog>
#include <QObject>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QGridLayout;
class QPushButton;
QT_END_NAMESPACE

namespace parview
{
	class GLWidget;
	class solveDialog : public QDialog
	{
		Q_OBJECT

	public:
		solveDialog();
		solveDialog(GLWidget *gl);
		~solveDialog();

		bool callDialog();

		float simTime;
		float timeStep;
		float saveTime;

		QString caseName;
		QString basePath;

	private:
		QDialog *solveDlg;

		QLineEdit *LEWorldOrigin;
		QLineEdit *LEGridSize;
		QLineEdit *LECaseName;
		QLineEdit *LEBasePath;
		QLineEdit *LESimTime;
		QLineEdit *LETimeStep;
		QLineEdit *LESaveStep;
		QGridLayout *solveLayout;
		QPushButton *PBSolve;
		QPushButton *PBCancel;

// 		vector3<float> worldOrigin;
// 		vector3<unsigned int> gridSize;

		GLWidget *GL;

		bool isDialogOk;

	private slots:
		void Click_Solve();
		void Click_Cancel();
	};
}

#endif