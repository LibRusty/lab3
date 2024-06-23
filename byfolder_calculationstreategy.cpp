#include "ByFolder_CalculationStrategy.h"

QMap<QString, qint64> ByFolder_CalculationStrategy::SomeCalculationMethod(const QString& path)
{
    std::shared_ptr<QDir> dir = std::make_shared<QDir>(path);
    QMap<QString, qint64> result;
    dir->setFilter(QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    qint64 total = 0;
    QFileInfoList list = dir->entryInfoList(); // считаем для папок
    for (auto fileinfo_iterator = list.begin(); fileinfo_iterator != list.end(); fileinfo_iterator++)
    {
        result[fileinfo_iterator->fileName()] = GetSize(fileinfo_iterator->absoluteFilePath());
        total += result[fileinfo_iterator->fileName()];
    }
    std::shared_ptr<QDir> dir1 = std::make_shared<QDir>(path);
    dir1->setFilter(QDir::Files);
    list = dir1->entryInfoList();
    qint64 size_cur = 0;
    for (auto fileinfo_iterator = list.begin(); fileinfo_iterator != list.end(); fileinfo_iterator++)
    {
        size_cur += fileinfo_iterator->size();
    }
    result["(Current folder)"] = size_cur;

    qint64 size_others = 0;
    for (auto x = result.begin(); x != result.end(); x++)
    {
        if (x.value() < 0.01 * total)
        {
            size_others += x.value();
            result.erase(x);
            x--;
        }
    }
    if (size_others)
        result["Others"] = size_others;
    return result;
}

qint64 ByFolder_CalculationStrategy::GetSize(const QString& path)
{
    qint64 size = 0;
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QFileInfoList list = dir.entryInfoList();
    for (auto fileinfo_iterator = list.begin(); fileinfo_iterator != list.end(); fileinfo_iterator++)
    {
        size += GetSize(fileinfo_iterator->absoluteFilePath());
    }
    if (list.isEmpty())
    {
        QFile f(path);
        size += f.size();
    }
    return size;
}
