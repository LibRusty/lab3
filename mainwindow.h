#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include "fileexplorermodel.h"
#include "byfiletype_calculationstrategy.h"
#include "byfolder_calculationstrategy.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
private slots:
	void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void SetStrategy(int index);
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
    void Calculation(QString path);
private:
    FileExplorerModel *fileModel;
	QFileSystemModel *dirModel;
	QTreeView *treeView;
	QTableView *tableView;
    CalculationStrategy* calculation; // стратегия подсчёта
    IAdapter* adapter; // адаптер
};

#endif // MAINWINDOW_H
