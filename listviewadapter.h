#ifndef LISTVIEWADAPTER_H
#define LISTVIEWADAPTER_H

#include "filebrowserobserver.h"
#include "fileexplorermodel.h"
#include <QTableView>

class ListViewAdapter: public FileBrowserObserver
{
public:
    ListViewAdapter(FileExplorerModel * f, QTableView t) {model = f; table = t; table->setModel(model);}
    void UpdateDisplay(QMap<QString, qint64> data)
    {
        model->setData(data);
        table->reset();
    }
    ~ListViewAdapter() {delete piechart;}
private:
    FileExplorerModel *model;
    QTableView* table;
};

#endif // LISTVIEWADAPTER_H
