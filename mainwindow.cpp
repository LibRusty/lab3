#include "mainwindow.h"
#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QTableView>
#include <QHeaderView>
#include <QStatusBar>
#include <QDebug>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
	//Устанавливаем размер главного окна
    this->setWindowTitle("Storage Explorer");
	this->setGeometry(100, 100, 1500, 500);
	this->setStatusBar(new QStatusBar(this));
	this->statusBar()->showMessage("Choosen Path: ");

    QWidget* widget = new QWidget(this);
    QGridLayout* layout = new QGridLayout(widget);
    widget->setLayout(layout);

    calculation = new ByFolder_CalculationStrategy();

    //создаём слой с виджетами выбора стратегии 
    QLabel* calc_txt = new QLabel("Action: ", this);
    QComboBox* action_choice = new QComboBox(this); // виджет выбора стратегии
    QStringList list_choice_action;
    list_choice_action << "Group file size by folders" << "Group file size by file type";
    action_choice->addItems(list_choice_action);
    action_choice->setCurrentIndex(0);

    layout->addWidget(calc_txt, 0, 0);
    layout->addWidget(action_choice, 0, 1);

    QLabel* view_txt = new QLabel("View: ", this);
    QComboBox* view_choice = new QComboBox(this); // виджет выбора вида
    QStringList list_choice_view;
    list_choice_view << "List View" << "Pie Chart" << "Bar Chart";
    view_choice->addItems(list_choice_view);
    view_choice->setCurrentIndex(0);

    layout->addWidget(view_txt, 0, 2);
    layout->addWidget(view_choice, 0, 3);

    //QString homePath = QDir::homePath(); // возвращает абсолютный путь к домашнему каталогу пользователя (C:/Users/Username)
    // Определим модель файловой системы:
    QString homePath = "C:/test";
    dirModel = new QFileSystemModel(this); // модель директории для дальнейшего отображения слева
	dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dirModel->setRootPath(homePath);

    QMap<QString, qint64> m = calculation->SomeCalculationMethod(homePath);
    FileExplorerModel* fileModel = new FileExplorerModel();
    //создаёт модель описания файловой системы справа

    // По умолчанию используем ListViewAdapter
    currentAdapter = new ListViewAdapter(fileModel);
    calculation->resetObserver(currentAdapter);
    calculation->OnFinish(m);

    QWidget* view = currentAdapter->getWidget();

    treeView = new QTreeView();
    treeView->setModel(dirModel); // для модели директории
    treeView->expandAll();

    splitter = new QSplitter(parent);
    splitter->addWidget(treeView);
    splitter->addWidget(view);

    layout->addWidget(splitter, 1, 0, 1, 4);
    setCentralWidget(widget);

    QItemSelectionModel *selectionModel = treeView->selectionModel();

    treeView->header()->resizeSection(0, 200);

	//Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_selectionChangedSlot);
    connect(action_choice, QOverload<int>::of(&QComboBox::currentIndexChanged), this, MainWindow::SetStrategy);
    connect(view_choice, QOverload<int>::of(&QComboBox::currentIndexChanged), this, MainWindow::SetView);
    //Пример организации установки курсора в TreeView относительно модельного индекса
	QItemSelection toggleSelection;
	QModelIndex topLeft;
	topLeft = dirModel->index(homePath);
	dirModel->setRootPath(homePath);

	toggleSelection.select(topLeft, topLeft);
	selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);

}
//Слот для обработки выбора элемента в TreeView
//выбор осуществляется с помощью курсора

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
	//Q_UNUSED(selected);
	Q_UNUSED(deselected);
	QModelIndexList indexs =  selected.indexes();
	QString filePath = "";

	// Размещаем инфо в statusbar относительно выделенного модельного индекса

	if (indexs.count() >= 1) {
		QModelIndex ix =  indexs.constFirst();
		filePath = dirModel->filePath(ix);
		this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst()));
	}

    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    Calculation(filePath);
}

void MainWindow::SetStrategy(int index)
{
    switch(index)
    {
        case 0: calculation = new ByFolder_CalculationStrategy(); break;
        case 1: calculation = new ByFileType_CalculationStrategy(); break;
    }
    calculation->resetObserver(currentAdapter);
    Calculation(this->statusBar()->currentMessage().section(": ", 1,1).trimmed());
}

void MainWindow::SetView(int index)
{
    if (currentAdapter) {
        delete currentAdapter;
        currentAdapter = nullptr;
    }
    switch(index)
    {
        case 0:
        {
            FileExplorerModel* fileModel = new FileExplorerModel();
            currentAdapter = new ListViewAdapter(fileModel);
            break;
        }
        case 1:
        {
            currentAdapter = new PieChartAdapter();
            break;
        }
        case 2:
        {
            currentAdapter = new BarChartAdapter();
            break;
        }
    }
    calculation->resetObserver(currentAdapter);
    Calculation(this->statusBar()->currentMessage().section(": ", 1, 1).trimmed());
}

void MainWindow::Calculation(QString path)
{
    QMap<QString, qint64> m = calculation->SomeCalculationMethod(path);
    calculation->OnFinish(m);
    QWidget* newview = currentAdapter->getWidget();
    if (splitter->widget(1)) {
        splitter->replaceWidget(1, newview);
    }
    else
        splitter->addWidget(newview);
    splitter->setSizes(QList<int>{200, 200});
}

MainWindow::~MainWindow()
{
    delete dirModel;
    delete treeView;
    delete splitter;
    delete calculation;
    delete currentAdapter;
}
