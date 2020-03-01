#ifndef	CONTENTBROWSERITEM_H
#define CONTENTBROWSERITEM_H

#include <QString>
#include <QIcon>

struct ItemStruct
{
    QIcon mIcon;
    QString mName;
    QString mPath;
    QByteArray mCacheKey;
};

class ContentItem
{
public:
    ContentItem(ItemStruct itemProps);
    
    QIcon GetIcon() const;
    QString GetName() const;
    QString GetPath() const;
    QByteArray GetCacheKey() const;

private:
    QIcon mIcon;
    QString mName;
    QString mPath;
    QByteArray mCacheKey;
};

#endif