#include "contentbrowseritem.h"

ContentItem::ContentItem(ItemStruct itemProps)
{
    mIcon = itemProps.mIcon;
    mName = itemProps.mName;
    mPath = itemProps.mPath;
    mCacheKey = itemProps.mCacheKey;
}

QIcon ContentItem::GetIcon() const
{
    return mIcon;
}

QString ContentItem::GetName() const
{
    return mName;
}

QString ContentItem::GetPath() const
{
    return mPath;
}

QByteArray ContentItem::GetCacheKey() const
{
    return mCacheKey;
}
