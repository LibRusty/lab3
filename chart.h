#ifndef CHART_H
#define CHART_H
#include <QChart>
#include <QChartView>
#include <QAbstractSeries>
#include <QLegend>

#include "filedata.h"

class Chart
{
public:
    QtCharts::QChartView* CreateChart(QMap<QString, qint64>);
protected:
    virtual QtCharts::QChart* DrawChart(QMap<QString, qint64>);
    void DrawLegend(QtCharts::QChart&);
};


#endif // CHART_H
