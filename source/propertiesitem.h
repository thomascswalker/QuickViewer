#ifndef	PROPERTIESITEM_H
#define PROPERTIESITEM_H

#include <QString>
#include <QIcon>
#include <QVariant>

struct PropertyStruct
{
    QString mProperty;
    QVariant mValue;
};

class PropertyItem
{
public:
    PropertyItem(PropertyStruct properties);

    QString GetProperty() const;
    QVariant GetValue() const;
    void SetValue(QVariant value);

private:
    QString mProperty;
    QVariant mValue;
};

#endif