#include "propertiesmodel.h"

PropertiesModel::PropertiesModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int PropertiesModel::rowCount(const QModelIndex& parent) const
{
    return mProperties.count();
}

int PropertiesModel::columnCount(const QModelIndex& parent) const
{
    return 2;
}

QVariant PropertiesModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= mProperties.size() || index.row() < 0)
    {
        return QVariant();
    }

    if (index.column() == 1 && role == Qt::TextAlignmentRole)
    {
        return Qt::AlignLeft;
    }

    if (role != Qt::CheckStateRole)
    {
        ContentItem item = mProperties.at(index.row());
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

QVariant PropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && section == 0)
    {
        return QVariant("Property");
    }
    else if (role == Qt::DisplayRole && section == 1)
    {
        return QVariant("Value");
    }

    return QVariant();
}

QHash<int, QByteArray> PropertiesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IconRole] = "icon";
    roles[NameRole] = "name";
    roles[PathRole] = "path";
    roles[CacheKeyRole] = "cachekey";
    return roles;
}
