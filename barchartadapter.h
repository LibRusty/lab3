#ifndef BARCHARTADAPTER_H
#define BARCHARTADAPTER_H

#include "filebrowserobserver.h"
#include "barchart.h"

class BarChartAdpater: public FileBrowserObserver
{
public:
    BarChartAdapter(BarChart* p) {barchart = p;}
    void UpdateDisplay(QMap<QString, qint64> data)
    {
        barchart->CreateChart(data);
    }
    ~BarChartAdapter() {delete barchart;}
private:
    BarChart* barchart;
};

#endif // BARCHARTADAPTER_H
