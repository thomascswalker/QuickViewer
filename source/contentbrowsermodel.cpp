#include "contentbrowsermodel.h"

ContentBrowserModel::ContentBrowserModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void ContentBrowserModel::addContentItem(const ContentItem& item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mContentItems << item;
    endInsertRows();
}

int ContentBrowserModel::rowCount(const QModelIndex& parent) const
{
    return mContentItems.count();
}

int ContentBrowserModel::columnCount(const QModelIndex& parent) const
{
    return 2;
}

QVariant ContentBrowserModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
        
    if (index.row() >= mContentItems.size() || index.row() < 0)
    {
        return QVariant();
    }

    if (role != Qt::CheckStateRole)
    {
        ContentItem item = mContentItems.at(index.row());
        if (index.column() == 0)
        {
            return item.GetIcon();
        }
        else if (index.column() == 1)
        {
            return item.GetName();
        }
    }

    return QVariant();
}

QVariant ContentBrowserModel::getData(const QModelIndex& index, int role) const
{
    ContentItem item = mContentItems.at(index.row());

    if (role == IconRole)
    {
        return item.GetIcon();
    }
    else if (role == NameRole)
    {
        return item.GetName();
    }
    else if (role == PathRole)
    {
        return item.GetPath();
    }
    else if (role == CacheKeyRole)
    {
        return item.GetCacheKey();
    }

    return QVariant();
}

bool ContentBrowserModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid())
    {
        emit(dataChanged(index, index));
        return true;
    }

    return false;
}


QHash<int, QByteArray> ContentBrowserModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IconRole] = "icon";
    roles[NameRole] = "name";
    roles[PathRole] = "path";
    roles[CacheKeyRole] = "cachekey";
    return roles;
}
