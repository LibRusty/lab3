#ifndef BARCHART_H
#define BARCHART_H
#include "chart.h"
#include <QStackedBarSeries>

class BarChart: public Chart
{
    QtCharts::QChart* DrawChart(QMap<QString, qint64> data)
    {
        QtCharts::QChart* bar_chart = new QtCharts::QChart();
        QtCharts::QStackedBarSeries* series = new QtCharts::QStackedBarSeries(bar_chart);

        QList<QtCharts::QBarSet*> barset;
        for (auto x: data)
        {
            QtCharts::QBarSet* s = new QtCharts::QBarSet(x.first);
            *s << x.second;
            barset.push_back(s);
        }
        series->append(barset);

        pie_chart->addSeries(series);
        return pie_chart;
    }
};

#endif // BARCHART_H
