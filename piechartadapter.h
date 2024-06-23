#ifndef PIECHARTADAPTER_H
#define PIECHARTADAPTER_H

#include "filebrowserobserver.h"
#include "PieChart.h"

class PieChartAdapter: public FileBrowserObserver
{
public:
    PieChartAdapter(QtCharts::QChart* p = nullptr)
    {
        piechart = p;
    }
    void UpdateDisplay(QMap<QString, qint64> data)
    {
        delete piechart;
        PieChart p;
        piechart = p.CreateChart(Action(data));
    }
    QWidget* getWidget()
    {
        QtCharts::QChartView* view = new QtCharts::QChartView(piechart);
        return view;
    }
    ~PieChartAdapter() {delete piechart;}
private:
    QMap<QString, qreal> Action(QMap<QString, qint64>& v);
    QtCharts::QChart* piechart;
};

#endif // PIECHARTADAPTER_H
