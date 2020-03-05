#ifndef	PROPERTIESMODEL_H
#define PROPERTIESMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>
#include <QList>
#include <QStandardItem>

#include "propertiesitem.h"

class PropertiesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PropertiesRoles {
        PropRole = Qt::UserRole + 1,
        ValueRole = Qt::UserRole + 2
    };

    PropertiesModel(QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent) const;
    void addProperty(const QString name, const QVariant value);
    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<PropertyItem> mProperties;
};

#endif