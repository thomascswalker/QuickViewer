#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>

//![0]
class FileListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    FileListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

signals:
    void numberPopulated(int number);

public slots:
    void setDirPath(const QString& path);

protected:
    bool canFetchMore(const QModelIndex& parent) const override;
    void fetchMore(const QModelIndex& parent) override;

private:
    QStringList fileList;
    int fileCount;
};
//![0]

#endif // FILELISTMODEL_H