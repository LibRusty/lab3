#ifndef MAINWINDOW_FILEBROWSER_H
#define MAINWINDOW_FILEBROWSER_H

#include "ByFileType_CalculationStrategy.h"
#include "ByFolder_CalculationStrategy.h"

class MainWindow_FileBrowser
{
public:
    MainWindow_FileBrowser(CalculationStrategy* strategy): calculation(strategy){}
    ~MainWindow_FileBrowser(){delete calculation;}
    void SetStrategy(CalculationStrategy* strategy) {calculation = strategy;}
    QMap<QString, qint64> Calculation(const QString& path)
    {return calculation->SomeCalculationMethod(path);}
private:
    CalculationStrategy *calculation;
};

#endif // MAINWINDOW_FILEBROWSER_H
