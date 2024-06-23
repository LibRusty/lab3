#ifndef FILEBROWSEROBSERVER_H
#define FILEBROWSEROBSERVER_H

#include <QMap>
#include <QWidget>
class FileBrowserObserver
{
public:
    virtual void UpdateDisplay(QMap<QString, qint64> data) = 0;
    virtual QWidget* getWidget() = 0;
};

#endif // FILEBROWSEROBSERVER_H
