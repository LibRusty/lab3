#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H

#include <memory>
#include <QDir>
#include <QVector>
#include <QPair>
#include <iostream>
#include <QDebug>
#include <QMap>

class CalculationStrategy
{
public:
    virtual QMap<QString, qint64> SomeCalculationMethod(const QString& path) = 0;
    virtual ~CalculationStrategy() = default;
};


#endif // CALCULATIONSTRATEGY_H
