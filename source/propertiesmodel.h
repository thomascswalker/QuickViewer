#ifndef	PROPERTIESMODEL_H
#define PROPERTIESMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>

#include "contentbrowseritem.h"

class PropertiesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PropertiesRoles {
        IconRole = Qt::UserRole + 1,
        NameRole = Qt::UserRole + 2,
        PathRole = Qt::UserRole + 3,
        CacheKeyRole = Qt::UserRole + 4
    };

    PropertiesModel(QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ContentItem> mProperties;
};

#endif