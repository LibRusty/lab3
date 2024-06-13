#include "fileexplorermodel.h"

FileExplorerModel::FileExplorerModel(QObject *parent, QList<FileData> list): QFileSystemModel(parent)
{
    dataModel = list;
}

int FileExplorerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return dataModel.count();
}

int FileExplorerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return PERCENT + 1;
}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Vertical) {
        return section;
    }
    switch (section) {
    case NAME:
        return "Название";
    case SIZE:
        return "Размер в байтах";
    case PERCENT:
        return "В процентах";
    }
    return QVariant();
}

QVariant FileExplorerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || dataModel.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
        return QVariant();
    }
    if (index.column() == 0) {
        return dataModel[index.row()].name;
    } else if (index.column() == 1) {
        return dataModel[index.row()].size;
    } else if (index.column() == 2) {
        return dataModel[index.row()].percent;
    }
}
