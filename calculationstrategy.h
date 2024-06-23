#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H

#include <memory>
#include <QDir>
#include <QVector>
#include <QPair>
#include <iostream>
#include <QDebug>
#include <QMap>

#include "filebrowserobserver.h"

class CalculationStrategy
{
public:
    virtual QMap<QString, qint64> SomeCalculationMethod(const QString& path) = 0;
    virtual ~CalculationStrategy() {delete observer;}

    virtual void OnFinish(QMap<QString, qint64> data)
    {
        observer->UpdateDisplay(data);
    }
    virtual void resetObserver(FileBrowserObserver* f)
    {
        observer = f;
    }
private:
    FileBrowserObserver* observer;
};


#endif // CALCULATIONSTRATEGY_H
