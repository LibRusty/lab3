#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include "byfiletype_calculationstrategy.h"
#include "byfolder_calculationstrategy.h"
#include "piechartadapter.h"
#include "barchartadapter.h"
#include "listviewadapter.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
private slots:
	void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void SetStrategy(int index);
    void SetView(int index);
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
    void Calculation(QString path);
	QFileSystemModel *dirModel;
	QTreeView *treeView;

    CalculationStrategy* calculation; // стратегия подсчёта
    FileBrowserObserver* currentAdapter; // адаптер

    QSplitter *splitter;
};

#endif // MAINWINDOW_H
