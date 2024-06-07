#include "ByFolder_CalculationStrategy.h"

QMap<QString, qint64> ByFolder_CalculationStrategy::SomeCalculationMethod(const QString& path)
{
    std::shared_ptr<QDir> dir = std::make_shared<QDir>(path);
    QMap<QString, qint64> result;
    dir->setFilter(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    QFileInfoList list = dir->entryInfoList();
    for (auto fileinfo_iterator = list.begin(); fileinfo_iterator != list.end(); fileinfo_iterator++)
    {
        result[fileinfo_iterator->fileName()] = GetSize(fileinfo_iterator->absoluteFilePath());
    }
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
