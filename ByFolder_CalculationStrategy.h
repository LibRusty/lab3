#ifndef BYFOLDER_CALCULATIONSTRATEGY_H
#define BYFOLDER_CALCULATIONSTRATEGY_H

#include "calculationstrategy.h"

class ByFolder_CalculationStrategy: public CalculationStrategy
{
public:
    QMap<QString, qint64> SomeCalculationMethod(const QString& path) override;
private:
    qint64 GetSize(const QString& path);
};

#endif // BYFOLDER_CALCULATIONSTRATEGY_H
