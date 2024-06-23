#include "piechartadapter.h"

QMap<QString, qreal> PieChartAdapter::Action(QMap<QString, qint64>& v)
{
    qint64 dir_size = 0;
    for (auto x = v.keyValueBegin(); x != v.keyValueEnd(); x++)
    {
        dir_size += x->second;
    }

    QMap<QString, qreal> list = QMap<QString, qreal>();
    for (auto x = v.keyValueBegin(); x != v.keyValueEnd(); x++)
    {
        QString name = x->first; // для того, чтобы затем на основе этого создать объект типа FileData
        QString size = QString::number(x->second);

        qreal percent = qreal(x->second) / qreal(dir_size);
        qreal p = qRound64(percent * 10000.0) / 100.0;
        if (x->second == 0 && v.size() > 1)
        {
            list[name] = 0;
        }
        else if (p == 100 && v.size() > 1) // несколько объектов, но один из них почти 100%
        {
            list[name] = 99.99;
        }
        else if (v.size() == 1) // один элемент в файле
        {
            list[name] = p;
        }
        else
        {
            list[name] = p;
        }
    }
    return list;
}
