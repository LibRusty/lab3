#ifndef BARCHARTADAPTER_H
#define BARCHARTADAPTER_H

#include "filebrowserobserver.h"
#include "barchart.h"

class BarChartAdapter: public FileBrowserObserver
{
public:
    BarChartAdapter(QtCharts::QChart* p = nullptr) {barchart = p;}
    void UpdateDisplay(QMap<QString, qint64> data)
    {
        BarChart b;
        barchart = b.CreateChart(data);
    }
    QWidget* getWidget()
    {
        QtCharts::QChartView* view = new QtCharts::QChartView(barchart);
        return view;
    }
    ~BarChartAdapter() {delete barchart;}
private:
    QtCharts::QChart* barchart;
};

#endif // BARCHARTADAPTER_H
