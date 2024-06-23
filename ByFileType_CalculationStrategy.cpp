#include "ByFileType_CalculationStrategy.h"

QMap<QString, qint64> ByFileType_CalculationStrategy::SomeCalculationMethod(const QString& path)
{
    QMap<QString, qint64> map;
    GetSize(path, map);
    qint64 total = 0;
    for (auto x = map.begin(); x != map.end(); x++)
        total += x.value();
    qint64 size_others = 0;
    for (auto x = map.begin(); x != map.end(); x++)
    {
        if (x.value() < 0.01 * total)
        {
            size_others += x.value();
            map.erase(x);
            x--;
        }
    }
    if (size_others)
        map["Others"] = size_others;
    return map;
}

void ByFileType_CalculationStrategy::GetSize(const QString &path, QMap<QString, qint64> &map)
{
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for (auto fileinfo_iterator = list.begin(); fileinfo_iterator != list.end(); fileinfo_iterator++)
    {
        if (fileinfo_iterator->isDir())
        {
            GetSize(fileinfo_iterator->absoluteFilePath(), map);
        }
        else if (fileinfo_iterator->isFile())
        {
            QString extension = fileinfo_iterator->suffix();
            if (map.contains(extension)) {
                map[extension] += fileinfo_iterator->size();
            } else {
                map[extension] = fileinfo_iterator->size();
            }
        }
    }
}
