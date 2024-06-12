#ifndef BYFILETYPE_CALCULATIONSTRATEGY_H
#define BYFILETYPE_CALCULATIONSTRATEGY_H

#include "calculationstrategy.h"

class ByFileType_CalculationStrategy: public CalculationStrategy
{
public:
    QMap<QString, qint64> SomeCalculationMethod(const QString& path) override;
private:
    void GetSize(const QString& path, QMap<QString, qint64>& map);
};

#endif // BYFILETYPE_CALCULATIONSTRATEGY_H
