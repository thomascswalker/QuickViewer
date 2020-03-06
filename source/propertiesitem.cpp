#include "propertiesitem.h"

PropertyItem::PropertyItem(PropertyStruct itemProps)
{
    mProperty = itemProps.mProperty;
    mValue = itemProps.mValue;
}

QString PropertyItem::GetProperty() const
{
    return mProperty;
}

QVariant PropertyItem::GetValue() const
{
    return mValue;
}

void PropertyItem::SetValue(QVariant value)
{
    mValue = value;
}