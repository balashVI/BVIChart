#include "charts_plugin.h"
#include "piechartcanvas.h"
#include "polarareachartcanvas.h"
#include "chartpopup.h"
#include "chartaxis.h"
#include "pieslice.h"
#include "xychart.h"
#include "chartheader.h"
#include "chartfont.h"

#include <qqml.h>

void ChartsPlugin::registerTypes(const char *uri)
{
    // @uri BVI.Charts
    qmlRegisterType<PieChartCanvas>(uri, 1, 0, "PieChartCanvas");
    qmlRegisterType<PolarAreaChartCanvas>(uri, 1, 0, "PolarAreaChartCanvas");
    qmlRegisterType<ChartPopup>(uri, 1, 0, "ChartPopup");
    qmlRegisterType<ChartAxis>(uri, 1, 0, "ChartAxis");
    qmlRegisterType<PieSlice>(uri, 1, 0, "PieSlice");
    qmlRegisterType<XYChart>(uri, 1, 0, "XYChart");
    qmlRegisterType<ChartHeader>(uri, 1, 0, "ChartHeader");
    qmlRegisterType<ChartFont>(uri, 1, 0, "ChartFont");
}


