#ifndef BARCHART_H
#define BARCHART_H
#include "chart.h"
#include <QBarSeries>
#include <QBarSet>

class BarChart: public Chart
{
    QtCharts::QChart* DrawChart(QMap<QString, qreal> data)
    {
        QtCharts::QChart* bar_chart = new QtCharts::QChart();
        QtCharts::QBarSeries* series = new QtCharts::QBarSeries(bar_chart);

        QList<QtCharts::QBarSet*> barset;
        for (auto x = data.begin(); x != data.end(); x++)
        {
            QtCharts::QBarSet* s = new QtCharts::QBarSet(x.key() + " (" + QString::number(x.value()) + "%)");
            s->append(x.value());
            barset.push_back(s);
        }
        series->append(barset);

        bar_chart->addSeries(series);
        return bar_chart;
    }
};

#endif // BARCHART_H
