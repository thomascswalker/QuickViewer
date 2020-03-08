#ifndef	QUICKVIEWER_H
#define QUICKVIEWER_H

#include "ui_QuickViewer.h"
#include "fileloader.h"
#include "framebuffer.h"
#include "contentbrowsermodel.h"
#include "propertiesmodel.h"

#include <QtGlobal>
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QFileSystemModel>
#include <QStorageInfo>
#include <QStyleFactory>
#include <QLibraryInfo>
#include <QTextBrowser>
#include <QFileInfo>
#include <QImageReader>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QScrollBar>
#include <QRectF>

namespace Ui {
	class QuickViewer;
}

class QuickViewer : public QMainWindow
{
	Q_OBJECT

public:
	explicit QuickViewer(QWidget *parent = Q_NULLPTR);
	~QuickViewer();
	void setupFramebuffer();
	void setupPalette();
	void setupModels();

public slots:
	void resizeEvent(QResizeEvent*);

	void on_zoomPercentChanged(int percent);
	void on_zoomMiddleMouseScroll(double zoom);
	void on_directoryLoaded(QString path);
	void on_actionAboutClicked();
	void on_lineEditChanged(QString path);
	void on_fileViewItemClicked(QModelIndex index);
	void on_folderUpClicked();
	void on_loadFilesClicked();

	void on_contentBrowserItemSelected(const QItemSelection& fromItem, const QItemSelection& toItem);
	void on_contentBrowserItemClicked(const QModelIndex& index);

private:
	Ui::QuickViewerClass* ui;
	Framebuffer* buffer;
	QFileSystemModel* fileModel;
	ContentBrowserModel* contentModel;
	PropertiesModel* propertiesModel;

	QGraphicsScene* scene;
	QGraphicsPixmapItem* scenePixmap;

	qreal currentScale = 1.0;
	QSize origSize;
	QSize dispSize;
	QSize proxySize;
};

#endif