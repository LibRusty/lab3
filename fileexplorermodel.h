#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H
#include <QFileSystemModel>
#include <QMap>
#include "adapter.h"
#include "QStandardItemModel"

class FileExplorerModel: public QFileSystemModel
{
public:
    FileExplorerModel(QObject *parent = nullptr, QList<FileData> list = QList<FileData>());

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    enum NameColumn { //перечисление
        NAME = 0,
        SIZE,
        PERCENT
    };
    QList<FileData> dataModel;
};

#endif // FILEEXPLORERMODEL_H
