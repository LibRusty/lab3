#include <QCoreApplication>
#include "mainwindow_filebrowser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ByFolder_CalculationStrategy f;
    ByFileType_CalculationStrategy g;
    QString str = "C:/lab3/test/test3"; // путь к папке
    MainWindow_FileBrowser browser(&f);
    //MainWindow_FileBrowser browser(&g);
    QMap<QString, qint64> v = browser.Calculation(str);

    qint64 dir_size = 0;
    for (auto x = v.keyValueBegin(); x != v.keyValueEnd(); x++)
    {
        dir_size += x->second;
    }
    qDebug() << "Current folder: " << str;
    QDir dir(str);
    if (!dir.exists())
        qDebug() << "Folder doesn't exists";
    else if (dir.exists() && v.size() == 0)
        qDebug() << "Folder exists but it's empty";
    for (auto x = v.keyValueBegin(); x != v.keyValueEnd(); x++)
    {
        qreal percent = qreal(x->second) / qreal(dir_size);
        qreal p = qRound64(percent * 10000.0) / 100.0;
        if (x->second == 0 && v.size() > 1)
        {
            qDebug() << x->first << " " << "0%";
        }
        else if (p == 100 && v.size() > 1) // несколько объектов, но один из них почти 100%
        {
            qDebug() << x->first << " " << "99.99%";
        }
        else if (v.size() == 1) // один элемент в файле
        {
            qDebug() << x->first << " " << p << "%";
        }
        else if (p < 0.01)
        {
            qDebug() << x->first << " " << "<0.01%";
        }
        else
        {
            qDebug() << x->first << " " << p << "%";
        }
    }
    return a.exec();
}
