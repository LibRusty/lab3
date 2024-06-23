#ifndef BYFILETYPE_CALCULATIONSTRATEGY_H
#define BYFILETYPE_CALCULATIONSTRATEGY_H

#include "calculationstrategy.h"

class ByFileType_CalculationStrategy: public CalculationStrategy
{
public:
    QMap<QString, qint64> SomeCalculationMethod(const QString& path) override;
    void OnFinish(QMap<QString, qint64> data)
    {
        observer->UpdateDisplay(data);
    }
    void resetObserver(FileBrowserObserver* f)
    {
        observer = f;
    }
    ~ByFileType_CalculationStrategy() {delete observer;}
private:
    FileBrowserObserver* observer;
private:
    void GetSize(const QString& path, QMap<QString, qint64>& map);
};

#endif // BYFILETYPE_CALCULATIONSTRATEGY_H
