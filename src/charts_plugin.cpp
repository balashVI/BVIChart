#include "charts_plugin.h"
#include "pieslice.h"
#include "xychart.h"
#include "chartfont.h"
#include "barchart.h"
#include "barseries.h"
#include "categoryaxis.h"
#include "chartpen.h"
#include "standartaxis.h"
#include "piechart.h"

#include <qqml.h>

void ChartsPlugin::registerTypes(const char *uri)
{
    // @uri BVI.Charts
    qmlRegisterType<PieSlice>(uri, 1, 0, "PieSlice");
    qmlRegisterType<PieChart>(uri, 1, 0, "PieChart");
    qmlRegisterType<XYChart>(uri, 1, 0, "XYChart");
    qmlRegisterType<ChartFont>(uri, 1, 0, "ChartFont");
    qmlRegisterType<BarChart>(uri, 1, 0, "BarChart");
    qmlRegisterType<BarSeries>(uri, 1, 0, "BarSeries");
    qmlRegisterType<CategoryAxis>(uri, 1, 0, "CategoryAxis");
    qmlRegisterType<StandartAxis>(uri, 1, 0, "StandartAxis");
    qmlRegisterType<ChartPen>(uri, 1, 0, "ChartPen");
}


