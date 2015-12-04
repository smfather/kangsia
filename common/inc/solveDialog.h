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

		void callDialog();

	private:
		QDialog *solveDlg;

		QLabel *LCaseName;
		QLabel *LBasePath;
		QLabel *LSimTime;
		QLabel *LTimeStep;
		QLabel *LSaveStep;
		QLineEdit *LECaseName;
		QLineEdit *LEBasePath;
		QLineEdit *LESimTime;
		QLineEdit *LETimeStep;
		QLineEdit *LESaveStep;
		QGridLayout *solveLayout;
		QPushButton *PBSolve;
		QPushButton *PBCancel;

		GLWidget *GL;

	private slots:
		void Click_Solve();
		void Click_Cancel();
	};
}

#endif