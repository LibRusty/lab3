#ifndef LISTVIEWADAPTER_H
#define LISTVIEWADAPTER_H

#include "filebrowserobserver.h"
#include "fileexplorermodel.h"
#include <QTableView>

class ListViewAdapter: public FileBrowserObserver
{
public:
    ListViewAdapter(FileExplorerModel* f)
    {
        model = f;
        table = new QTableView();
        table->setModel(model);
    }
    void UpdateDisplay(QMap<QString, qint64> data)
    {
        model->setData(Action(data));
        table->reset();
    }
    QWidget* getWidget()
    {
        return table;
    }
    ~ListViewAdapter() {delete table; delete model;}
private:
    QList<FileData> Action(QMap<QString, qint64>& v);
    FileExplorerModel *model;
    QTableView* table;
};

#endif // LISTVIEWADAPTER_H
