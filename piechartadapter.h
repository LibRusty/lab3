#ifndef PIECHARTADAPTER_H
#define PIECHARTADAPTER_H

#include "filebrowserobserver.h"
#include "PieChart.h"

class PieChartAdpater: public FileBrowserObserver
{
public:
    PieChartAdapter(PieChart* p) {piechart = p;}
    void UpdateDisplay(QMap<QString, qint64> data)
    {
        piechart->CreateChart(data);
    }
private:
    PieChart* piechart;
};

#endif // PIECHARTADAPTER_H
