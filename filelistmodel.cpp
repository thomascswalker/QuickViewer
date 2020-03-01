#include "filelistmodel.h"

#include <QGuiApplication>
#include <QDir>
#include <QPalette>

FileListModel::FileListModel(QObject* parent)
    : QAbstractListModel(parent), fileCount(0)
{}

//![4]
int FileListModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : fileCount;
}

QVariant FileListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= fileList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return fileList.at(index.row());
    }
    else if (role == Qt::BackgroundRole) {
        int batch = (index.row() / 100) % 2;
        if (batch == 0)
            return qApp->palette().base();
        else
            return qApp->palette().alternateBase();
    }
    return QVariant();
}
//![4]

//![1]
bool FileListModel::canFetchMore(const QModelIndex& parent) const
{
    if (parent.isValid())
        return false;
    return (fileCount < fileList.size());
}
//![1]

//![2]
void FileListModel::fetchMore(const QModelIndex& parent)
{
    if (parent.isValid())
        return;
    int remainder = fileList.size() - fileCount;
    int itemsToFetch = qMin(100, remainder);

    if (itemsToFetch <= 0)
        return;

    beginInsertRows(QModelIndex(), fileCount, fileCount + itemsToFetch - 1);

    fileCount += itemsToFetch;

    endInsertRows();

    emit numberPopulated(itemsToFetch);
}
//![2]

//![0]
void FileListModel::setDirPath(const QString& path)
{
    QDir dir(path);

    beginResetModel();
    fileList = dir.entryList();
    fileCount = 0;
    endResetModel();
}
//![0]