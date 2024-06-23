#ifndef PIECHART_H
#define PIECHART_H

#include "chart.h"
#include <QPieSeries>

class PieChart: public Chart
{
    QtCharts::QChart* DrawChart(QMap<QString, qint64> data)
    {
        QtCharts::QChart* pie_chart = new QtCharts::QChart();
        QtCharts::QPieSeries* series = new QtCharts::QPieSeries(pie_chart);

        for (auto x = data.begin(); x != data.end(); x++)
        {
            series->append(x.key(), x.value());
        }

        pie_chart->addSeries(series);
        return pie_chart;
    }

};

#endif // PIECHART_H
