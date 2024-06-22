#ifndef ADAPTER_H
#define ADAPTER_H

#include "iadapter.h"

class Adapter: public IAdapter
{
public:
    QList<FileData> Action(QMap<QString, qint64>& v) override;
};

#endif // ADAPTER_H
