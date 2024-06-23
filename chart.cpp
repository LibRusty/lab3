#include "chart.h"

QtCharts::QChart* Chart::CreateChart(QMap<QString, qreal> data)
{
    QtCharts::QChart* chart = DrawChart(data);
    DrawLegend(*chart);
    return chart;
}

void Chart::DrawLegend(QtCharts::QChart& chart)
{
    chart.legend()->setVisible(true);
    chart.legend()->setAlignment(Qt::AlignRight);
}
