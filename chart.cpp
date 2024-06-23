#include "chart.h"

QtCharts::QChartView* Chart::CreateChart(QMap<QString, qint64> data)
{
    QtCharts::QChart* chart = DrawChart(data);
    DrawLegend(*chart);
    QtCharts::QChartView* chartview = new QtCharts::QChartView(chart);
    return chartview;
}

void Chart::DrawLegend(QtCharts::QChart& chart)
{
    chart.legend()->setVisible(true);
    chart.legend()->setAlignment(Qt::AlignBottom);
}
