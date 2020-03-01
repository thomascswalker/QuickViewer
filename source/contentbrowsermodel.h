#ifndef	CONTENTBROWSERMODEL_H
#define CONTENTBROWSERMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>

#include "contentbrowseritem.h"

class ContentBrowserModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ContentBrowserRoles {
        IconRole = Qt::UserRole + 1,
        NameRole = Qt::UserRole + 2,
        PathRole = Qt::UserRole + 3,
        CacheKeyRole = Qt::UserRole + 4
    };

    ContentBrowserModel(QObject* parent = 0);

    void addContentItem(const ContentItem& item);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant getData(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ContentItem> m_ContentItems;
};


#endif