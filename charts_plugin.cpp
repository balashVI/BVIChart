#include "charts_plugin.h"
#include "piechartcanvas.h"
#include "polarareachartcanvas.h"
#include "chartpopup.h"
#include "chartaxis.h"
#include "pieslice.h"

#include <qqml.h>

void ChartsPlugin::registerTypes(const char *uri)
{
    // @uri BVI.Charts
    qmlRegisterType<PieChartCanvas>(uri, 1, 0, "PieChartCanvas");
    qmlRegisterType<PolarAreaChartCanvas>(uri, 1, 0, "PolarAreaChartCanvas");
    qmlRegisterType<ChartPopup>(uri, 1, 0, "ChartPopup");
    qmlRegisterType<ChartAxis>(uri, 1, 0, "ChartAxis");
    qmlRegisterType<PieSlice>(uri, 1, 0, "PieSlice");
}


