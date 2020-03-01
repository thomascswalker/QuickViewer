#include "fileloader.h"

/*
	Returns a QPixmap of the loaded file, or an empty
	QPixmap if the file has already been loaded into
	the QPixmapCache.

	When passed in a file path, this function loads
	the image while generating a unique cache key
	to store in the QPixmapCache. 
*/
QPixmap FileLoader::loadFile(QString fileName)
{
	// Reader for all filetypes
	QImageReader reader;

	// Setup the reader and store the original size,
	// and set the display size to the original size (100% zoom)
	reader.setFileName(fileName);
	origSize = reader.size();

	// Get our unique cache key from the filename.
	QByteArray cachekey = getUniqueCacheKey(fileName);

	// Cache the loaded image with a unique MD5 hash.
	QPixmapCache pixmapcache;
	QPixmap retPixmap;

	// If the file is already found in the QPixmapCache,
	// just return an empty QPixmap.
	if (pixmapcache.find(cachekey, &retPixmap))
	{
		QPixmap emptyPixmap;
		return emptyPixmap;
	}
	// Otherwise we want to load the actual file.
	else
	{
		// Read the actual image from the disk
		QImage image;
		reader.read(&image);

		// Insert the image into the pixmap cache, defining
		// the cache limit by:
		//		pixelsWide * pixelsTall * bitDepth / 8
		// The divisor of 8 at the end is to convert bytes to bits.
		int depth = image.depth();
		pixmapcache.setCacheLimit(image.width() * image.height() * depth / 8);
		pixmapcache.insert(cachekey, QPixmap::fromImage(image));

		// Set the image label to the loaded pixmap, converted
		// from the loaded QImage
		retPixmap = QPixmap::fromImage(image).scaled(QSize(origSize.width(), origSize.height()));

		return retPixmap;
	}
}

/*
	Returns a QByteArray MD5 hash.

	When passed in a path, this generates an MD5 hash
	of the given path to store as a QByteArray in the
	pixmapcache.

	This is the "source of truth" for each file loaded,
	as well as the check for if the file already exists
	in the pixmapcache.
*/
QByteArray FileLoader::getUniqueCacheKey(QString path)
{
	return QCryptographicHash::hash(path.toUtf8(), QCryptographicHash::Md5).toHex();
}
