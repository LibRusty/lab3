#ifndef IADAPTER_H
#define IADAPTER_H

#include "filedata.h"
#include <QMap>

class IAdapter
{
public:
    virtual QList<FileData> Action(QMap<QString, qint64>&) = 0;
};

#endif // IADAPTER_H
