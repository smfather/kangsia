#include "parview.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	parview::parVIEW w;
	w.show();
	return a.exec();
}
