#include "QuickViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setAttribute(Qt::AA_UseDesktopOpenGL, true);
	QuickViewer w;
	w.show();
	return a.exec();
}
