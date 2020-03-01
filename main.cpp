#include "QuickViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QuickViewer w;
	w.show();
	return a.exec();
}
