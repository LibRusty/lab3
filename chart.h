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
    QtCharts::QChart* CreateChart(QMap<QString, qreal>);
protected:
    virtual QtCharts::QChart* DrawChart(QMap<QString, qreal>);
    virtual void DrawLegend(QtCharts::QChart&);
};


#endif // CHART_H
