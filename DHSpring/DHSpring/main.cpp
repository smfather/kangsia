#include "dhspring.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("eucKR"));
	DHSpring w;
	w.show();
	return a.exec();
}
