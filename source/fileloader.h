#ifndef FILELOADER_H
#define FILELOADER_H


#include <QPixmap>
#include <QPixmapCache>
#include <QByteArray>
#include <QImageReader>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QStandardItem>
#include <QSize>

class FileLoader
{
public slots:
	QPixmap loadFile(QString fileName);
	QByteArray getUniqueCacheKey(QString path);

private:
	QSize origSize;
};

#endif