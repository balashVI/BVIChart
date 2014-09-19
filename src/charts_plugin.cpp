#include "charts_plugin.h"
#include "pieslice.h"
#include "xychart.h"
#include "chartheader.h"
#include "chartfont.h"
#include "chartlegend.h"
#include "barchart.h"
#include "barseries.h"

#include <qqml.h>

void ChartsPlugin::registerTypes(const char *uri)
{
    // @uri BVI.Charts
    qmlRegisterType<PieSlice>(uri, 1, 0, "PieSlice");
    qmlRegisterType<XYChart>(uri, 1, 0, "XYChart");
    qmlRegisterType<ChartHeader>(uri, 1, 0, "ChartHeader");
    qmlRegisterType<ChartFont>(uri, 1, 0, "ChartFont");
    qmlRegisterType<ChartLegend>(uri, 1, 0, "ChartLegend");
    qmlRegisterType<BarChart>(uri, 1, 0, "BarChart");
    qmlRegisterType<BarSeries>(uri, 1, 0, "BarSeries");
}


