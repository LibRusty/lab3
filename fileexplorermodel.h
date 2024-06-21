#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H
#include <QFileSystemModel>
#include <QMap>
#include "adapter.h"
#include "QAbstractItemModel"

class FileExplorerModel: public QAbstractItemModel
{
public:
    FileExplorerModel(QObject *parent = nullptr, QList<FileData> list = QList<FileData>());
    void setData(QList<FileData> filedata);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    enum NameColumn { //перечисление
        NAME = 0,
        SIZE,
        PERCENT
    };
    QList<FileData> dataModel;
};

#endif // FILEEXPLORERMODEL_H
