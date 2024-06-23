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
    virtual ~CalculationStrategy() = default;

    virtual void OnFinish(QMap<QString, qint64>)
    {
        for (auto x: observers)
            x->updateDisplay(QMap<QString, qint64>);
    }
    virtual void addObserver(FileBrowserObserver* f)
    {
        observers.push_back(f);
    }
    virtual void removeObserver(FileBrowserObserver* f)
    {
        observers.erase(qFind(observers, f));
    }
private:
    QVector<FileBrowserObserver*> observers;
};


#endif // CALCULATIONSTRATEGY_H
