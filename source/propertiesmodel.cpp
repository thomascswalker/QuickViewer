#include "propertiesmodel.h"

PropertiesModel::PropertiesModel(QObject* parent)
    : QAbstractListModel(parent)
{
    addProperty(QString("Name"), QVariant());
    addProperty(QString("Path"), QVariant());
    //addProperty(QString("Size"), QVariant());
    //addProperty(QString("Type"), QVariant());
}

int PropertiesModel::rowCount(const QModelIndex& parent) const
{
    return mProperties.count();
}

int PropertiesModel::columnCount(const QModelIndex& parent) const
{
    return 2;
}

void PropertiesModel::addProperty(const QString name, const QVariant value)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    PropertyStruct properties;
    properties.mProperty = name;
    properties.mValue = value;
    mProperties << properties;

    endInsertRows();
}

QVariant PropertiesModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role == Qt::DecorationRole)
    {
        return QVariant();
    }

    if (index.row() >= mProperties.size() || index.row() < 0)
    {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignLeft;
    }
        
    if (role != Qt::CheckStateRole)
    {
        PropertyItem item = mProperties.at(index.row());
        if (index.column() == 0)
        {
            return item.GetProperty();
        }
        else if (index.column() == 1)
        {
            return item.GetValue();
        }
    }

    return QVariant();
}

bool PropertiesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.column() == 0)
    {
        return false;
    }

    if (index.isValid() && role == ValueRole)
    {
        mProperties[index.row()].SetValue(value);
        emit dataChanged(index, index);
    }

    return true;
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
    roles[PropRole] = "property";
    roles[ValueRole] = "value";
    return roles;
}
