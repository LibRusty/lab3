#ifndef FILEDATA_H
#define FILEDATA_H

#include <QString>

class FileData
{
public:
    FileData(QString n = "NULL", QString s = "NULL", QString p = "NULL")
    {
        name = n; size = s; percent = p;
    }
    QString name;
    QString percent;
    QString size;
};

#endif // FILEDATA_H
