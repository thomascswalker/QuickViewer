#include "QuickViewer.h"

/*
	Constructor
*/
QuickViewer::QuickViewer(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QuickViewerClass)
{
	// Initial UI setup functions
	ui->setupUi(this);
	setupFramebuffer();
	setupModels();
	setupPalette();

	// Connections for menu bar actions
	(void)connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(on_actionAboutClicked()));

	// Connections for standard GUI items
	(void)connect(ui->zoomPercent, SIGNAL(valueChanged(int)), this, SLOT(on_zoomPercentChanged(int)));
	(void)connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_lineEditChanged(QString)));
	(void)connect(ui->fileView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_fileViewItemClicked(QModelIndex)));
	(void)connect(ui->folderUp, SIGNAL(clicked()), this, SLOT(on_folderUpClicked()));
	(void)connect(ui->loadFiles, SIGNAL(clicked()), this, SLOT(on_loadFilesClicked()));

	// Connections for extended GUI items
	(void)connect(ui->contentBrowserView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_contentBrowserItemClicked(const QModelIndex&)));
	(void)connect(ui->contentBrowserView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(on_contentBrowserItemSelected(const QItemSelection&, const QItemSelection&)));

	// Connections for models
	(void)connect(fileModel, SIGNAL(directoryLoaded(QString)), this, SLOT(on_directoryLoaded(QString)));
}

/*
	Destructor
*/
QuickViewer::~QuickViewer()
{
	delete ui;
}

/*
	Returns void.

	This sets up the framebuffer scene and an empty
	pixmap as a placeholder.
*/
void QuickViewer::setupFramebuffer()
{
	scene = new QGraphicsScene(this);
	ui->framebuffer->setScene(scene);
	QPixmap emptyPixmap("");
	scenePixmap = scene->addPixmap(emptyPixmap);
}

/*
	Returns void.

	This sets up the respective models for
	the fileView and contentBrowserView items.
*/
void QuickViewer::setupModels()
{
	// Setup the file system model for file and folder
	// browsing.
	fileModel = new QFileSystemModel(this);
	ui->fileView->setModel(fileModel);
	fileModel->setRootPath("C:");
	ui->fileView->setRootIndex(fileModel->index("C:"));

	ui->lineEdit->setText(fileModel->rootPath());
	
	// Setup the model for currently-loaded
	// file viewing and loading.
	contentModel = new ContentBrowserModel();
	ui->contentBrowserView->setModel(contentModel);

	// Setup the model for currently-loaded
	// file viewing and loading.
	propertiesModel = new PropertiesModel();
	ui->contentPropertiesView->setModel(propertiesModel);
}

/*
	 Returns void.
	 
	 This sets up the color and style palette for all GUI elements in
	 the app. Adheres to a dark-style palette similar to those found in
	 3ds Max and Maya.
*/
void QuickViewer::setupPalette()
{
	//Stylesheet
	qApp->setStyle(QStyleFactory::create("Fusion"));

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(68, 68, 68));
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(46, 46, 46));
	darkPalette.setColor(QPalette::AlternateBase, QColor(68, 68, 68));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Button, QColor(68, 68, 68));
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	qApp->setPalette(darkPalette);
	qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

/*
	 Returns void.
	 
	 This is the main resize event for the mainWindow (QMainWindow).
	 
	 This resizes the pixmap currently in the framebuffer to maintain the
	 correct aspect ratio for the current pixmap being viewed.
 */
void QuickViewer::resizeEvent(QResizeEvent*)
{
	double factor = 1.0;
	//ui->framebuffer->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

/*
	 Returns void.

	 This is the action event for scaling the framebuffer from clicking
	 the zoomPercent spinner. This is to give finer control over zooming
	 compared to using the middle mouse to scroll.
 */
void QuickViewer::on_zoomPercentChanged(int percent)
{
	qreal scaleTo = 1.0 * percent / 100.0;
	qreal scaleFactor = scaleTo / currentScale;
	currentScale = scaleTo;
	ui->framebuffer->scale(scaleFactor, scaleFactor);
}

/*
	 Returns void. 

	 By default, QFileSystemModel needs to load the files it finds
	 on a separate thread, so there's a signal emitted once that's
	 complete.

	 This is needed to update the path for the lineEdit to
	 verify it's correct, and also to update the file count
	 from the loaded directory.
 */
void QuickViewer::on_directoryLoaded(QString path)
{
	ui->lineEdit->setText(path);

	QModelIndex parentIndex = ui->fileView->rootIndex();
	int count = fileModel->rowCount(parentIndex);
	ui->textBrowser->setText(tr("%1 files and folders found.").arg(count));
}

/*
	Returns void.

	This shows the simple About window for the program.
	This dialog is modal.
*/
void QuickViewer::on_actionAboutClicked()
{
	QMessageBox msgBox;
	msgBox.setText("Created by Tom Walker.");
	msgBox.exec();
}

/*
	Returns void.

	This is called when the user updates the text
	in the current directory lineEdit item. Changing
	this text needs to update the rootPath of the fileModel
	and then also reset the rootIndex of the fileView.

	Doing this will also trigger the on_directoryLoaded(QString)
	function.
*/
void QuickViewer::on_lineEditChanged(QString path)
{
	// We want to validate that the given path is in fact
	// a real path that exists. If it doesn't exist, we don't
	// want to update the fileModel root path.
	QFileInfo checkPath(path);
	if (checkPath.exists())
	{
		fileModel->setRootPath(path);
		ui->fileView->setRootIndex(fileModel->index(path));
	}
}

/*
	Returns void.

	This is called when the user clicks an item in the fileView
	GUI element. The default nature is to go inside a directory
	that's selected with only a single click, rather than
	double click. If the user clicks a file, nothing happens.
*/
void QuickViewer::on_fileViewItemClicked(QModelIndex index)
{
	QString currentPath = fileModel->rootPath();
	QString newPath = fileModel->filePath(index);

	QDir currentDir(currentPath);
	QFileInfo checkFolder(newPath);

	// We want 
	if (checkFolder.exists() && !checkFolder.isFile() || currentDir[0] == "." && !checkFolder.isFile())
	{
		fileModel->setRootPath(newPath);
		ui->fileView->setRootIndex(fileModel->index(newPath));
	}
}

/*
	Returns void.

	This is called when the user on the folder up button.
	This moves the current path up one folder.
*/
void QuickViewer::on_folderUpClicked()
{
	QString currentPath = fileModel->rootPath();

	// If the path is less than or equal to three characters,
	// matching the length of the root path of a drive, then
	// we want to just set the root path to a blank string which
	// tells the QFileSystemModel to show all root drives
	if (currentPath.length() <= 3)
	{
		fileModel->setRootPath("");
		ui->fileView->setRootIndex(fileModel->index(""));
		ui->lineEdit->setText("");
	}
	// Otherwise we want to just go up one folder, removing
	// the last leaf of the current path
	else
	{
		QString newPath = currentPath + "//..";
		QFileInfo checkFolder(newPath);

		if (checkFolder.exists() && !checkFolder.isFile())
		{
			fileModel->setRootPath(newPath);
			ui->fileView->setRootIndex(fileModel->index(newPath));
		}
	}

}

/*
	Returns void.

	This is called when the user hits the Load button.
	This will load all selected image files into the global
	pixmapcache (natively defined by Qt) in addition to loading
	each image thumbnail and its properties into the contentBrowserView.

	When loading into the pixmapcache, it will check to see if the
	image is already and inside, and if not (and the image is new)
	only _then_ will it load the image.
*/
void QuickViewer::on_loadFilesClicked()
{
	FileLoader loader;
	QStringList files;
	QItemSelectionModel* select = ui->fileView->selectionModel();
	QList<QModelIndex> selected = select->selectedRows();

	for (int i = 0; i < selected.size(); i++) {
		QString filename = fileModel->filePath(selected[i]);
		files << filename;
	}
	
	int i = 0;
	while (i < files.size())
	{
		// We want to get the first file from the selection
		QString filepath = files[i];

		// If the file does exist
		if (!filepath.isNull())
		{
			// We want to load the given filename
			// into a QPixmap.
			QPixmap pixmap = loader.loadFile(filepath);

			// If the pixmap we get back is NOT Null
			// then we want to increment the loop and set
			// the currently viewed pixmap in the framebuffer
			// to the current pixmap
			if (!pixmap.isNull())
			{
				i++;
				scene->clear();
				scenePixmap = scene->addPixmap(pixmap);
				scene->setSceneRect(scene->itemsBoundingRect());

				// Get the stripped filename
				QFileInfo fileInfo(QFile(filepath).fileName());
				QString filename(fileInfo.fileName());
				QByteArray cachekey = loader.getUniqueCacheKey(filepath);

				// Create the new content item and store the file's
				// metadata as properties.
				ItemStruct itemProps;
				itemProps.mIcon = QIcon(pixmap);
				itemProps.mName = filename;
				itemProps.mPath = filepath;
				itemProps.mCacheKey = cachekey;

				// Once the item has been created, we want to add it
				// to the content browser list of items
				ContentItem item(itemProps);
				contentModel->addContentItem(item);
			}
			// If the pixmap we get back IS Null
			// then we don't want to increment, and we'll
			// remove the file in the file array so it's
			// not loaded into the thumbnail array
			else
			{
				qDebug() << "Pixmap already exists in cache, deleting " << filepath << " from file list";
				files.removeAt(i);
			}
		}
		else
		{
			qDebug() << "Invalid file";
		}
	}
}

/*
	Returns void.

	This is called when the user double clicks an item in the content browser.
	We want to get the data of the currently double clicked item in order to do
	a few things:

	1. We want to load the image into the framebuffer
	2. We want to display its properties in the properties panel
	3. We want to display any image-specific modifications (exposure, colorspace, etc)
	that were saved with that particular image.
*/
void QuickViewer::on_contentBrowserItemClicked(const QModelIndex& index)
{
	QPixmap pixmap;
	QVariant cachekey = contentModel->getData(index, ContentBrowserModel::CacheKeyRole);
	QPixmapCache::find(cachekey.toByteArray(), &pixmap);

	scene->clear();
	scenePixmap = scene->addPixmap(pixmap);
	scene->setSceneRect(scene->itemsBoundingRect());

	propertiesModel->setData(index, QVariant("test"), PropertiesModel::ValueRole);
}

/*
	Returns void.

	Functionally the same as on_contentBrowserItemClicked, just
	allows for arrow movement in the table view instead of
	just mouse clicking.

	The item selection event, because we're using a table,
	passes the beginning item and the end item, from top left
	to bottom right. In our case, we're only doing single selection
	so there'll only ever be one item selected at a time.

	Because of this, we can just grab the "indexes" (which is
	only ever going to be 1) and just load that first index
	we find.
*/
void QuickViewer::on_contentBrowserItemSelected(const QItemSelection& fromItem, const QItemSelection& toItem)
{
	QModelIndexList indexes = fromItem.indexes();
	QModelIndex index = indexes[0];
	on_contentBrowserItemClicked(index);

	QVariant data = contentModel->getData(index, ContentBrowserModel::NameRole);
	propertiesModel->setData(index, data, PropertiesModel::ValueRole);
}