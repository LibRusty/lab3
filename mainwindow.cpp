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
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
	//Устанавливаем размер главного окна
    this->setWindowTitle("Storage Explorer");
	this->setGeometry(100, 100, 1500, 500);
	this->setStatusBar(new QStatusBar(this));
	this->statusBar()->showMessage("Choosen Path: ");

    //создаём слой с виджетами выбора стратегии
    QHBoxLayout* layout_choice = new QHBoxLayout(this);
    QLabel* calc_txt = new QLabel("Action: ", this);

    QComboBox* action_choice = new QComboBox(this); // виджет выбора стратегии
    QStringList list_choice_action;
    list_choice_action << "Group file size by folders" << "Group file size by file type";
    action_choice->addItems(list_choice_action);

    layout_choice->addWidget(calc_txt);
    layout_choice->addWidget(action_choice);

    QString homePath = QDir::homePath(); // возвращает абсолютный путь к домашнему каталогу пользователя (C:/Users/Username)
    // Определим модель файловой системы:
    dirModel = new QFileSystemModel(this); // модель директории для дальнейшего отображения слева
	dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dirModel->setRootPath(homePath);

    fileModel = new FileExplorerModel(this); // модель файловой системы для дальнейшего отображения справа
	fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    fileModel->setRootPath(homePath);
	//Показать как дерево, пользуясь готовым видом:

	treeView = new QTreeView();
    treeView->setModel(dirModel); // для модели директории

	treeView->expandAll();
	QSplitter *splitter = new QSplitter(parent);
    tableView = new QTableView();
	tableView->setModel(fileModel);
	splitter->addWidget(treeView);
	splitter->addWidget(tableView);

    QHBoxLayout* layout_view = new QHBoxLayout(this);
    layout_view->addWidget(splitter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(layout_choice);
    layout->addLayout(layout_view);

    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    adapter = new Adapter();

	QItemSelectionModel *selectionModel = treeView->selectionModel();
	QModelIndex rootIx = dirModel->index(0, 0, QModelIndex());//корневой элемент

	QModelIndex indexHomePath = dirModel->index(homePath);
	QFileInfo fileInfo = dirModel->fileInfo(indexHomePath);

    action_choice->setCurrentIndex(0);
    calculation = new ByFolder_CalculationStrategy();

	/* Рассмотрим способы обхода содержимого папок на диске.
	 * Предлагается вариант решения, которы может быть применен для более сложных задач.
	 * Итак, если требуется выполнить анализ содержимого папки, то необходимо организовать обход содержимого. Обход выполняем относительно модельного индекса.
	 * Например:*/
	if (fileInfo.isDir()) {
		/*
		 * Если fileInfo папка то заходим в нее, что бы просмотреть находящиеся в ней файлы.
		 * Если нужно просмотреть все файлы, включая все вложенные папки, то нужно организовать рекурсивный обход.
		*/
		QDir dir  = fileInfo.dir();

		if (dir.cd(fileInfo.fileName())) {
            /*
             Если зашли в папку, то пройдемся по контейнеру QFileInfoList ,полученного методом entryInfoList,
            */
			foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Type)) {
				qDebug() << inf.fileName() << "---" << inf.size();
			}
            dir.cdUp();//выходим из папки
		}
	}
	QDir dir = fileInfo.dir();

	foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDir::Type)) {
		qDebug() << inf.fileName() << "---" << inf.size();
	}

	treeView->header()->resizeSection(0, 200);
	//Выполняем соединения слота и сигнала который вызывается когда осуществляется выбор элемента в TreeView
    connect(selectionModel, QItemSelectionModel::selectionChanged, this, MainWindow::on_selectionChangedSlot);
    connect(action_choice, QComboBox::activated, this, MainWindow::SetStrategy);
	//Пример организации установки курсора в TreeView относит ельно модельного индекса
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
	QModelIndex index = treeView->selectionModel()->currentIndex();
	QModelIndexList indexs =  selected.indexes();
	QString filePath = "";

	// Размещаем инфо в statusbar относительно выделенного модельного индекса

	if (indexs.count() >= 1) {
		QModelIndex ix =  indexs.constFirst();
		filePath = dirModel->filePath(ix);
		this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst()));
	}

	//TODO: !!!!!
	/*
	Тут простейшая обработка ширины первого столбца относительно длины названия папки.
	Это для удобства, что бы при выборе папки имя полностью отображалась в  первом столбце.
	Требуется доработка(переработка).
	*/
	int length = 200;
	int dx = 30;

	if (dirModel->fileName(index).length() * dx > length) {
		length = length + dirModel->fileName(index).length() * dx;
		qDebug() << "r = " << index.row() << "c = " << index.column() << dirModel->fileName(index) << dirModel->fileInfo(
					 index).size();

	}

	treeView->header()->resizeSection(index.column(), length + dirModel->fileName(index).length());
	tableView->setRootIndex(fileModel->setRootPath(filePath));
}

void MainWindow::SetStrategy()
{
    switch(action_choice->setCurrentIndex()))
    {
        case 1: calculation = new ByFolder_CalculationStrategy(); break;
        case 2: calculation = new ByFileType_CalculationStrategy(); break;
    }
    QItemSelectionModel::selectionChanged;
}

QList<FileData> MainWindow::Calculation(const QString &path)
{
    return adapter->Action(calculation->SomeCalculationMethod(path));
}

MainWindow::~MainWindow()
{
    delete calculation;
    delete adapter;
}
