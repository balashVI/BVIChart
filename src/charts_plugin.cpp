#include "charts_plugin.h"
#include "pieslice.h"
#include "barchart.h"
#include "barseries.h"
#include "categoryaxis.h"
#include "chartpen.h"
#include "standartaxis.h"
#include "piechart.h"
#include "polararea.h"
#include "polarareachart.h"
#include "polarraxis.h"
#include "lineseries.h"
#include "linechart.h"
#include "chartpoint.h"
#include "xyseries.h"
#include "xychart.h"
#include "bubble.h"
#include "bubblechart.h"
#include "bubbleseries.h"

#include <qqml.h>

void ChartsPlugin::registerTypes(const char *uri)
{
    // @uri BVI.Charts
    qmlRegisterType<Bubble>(uri, 1, 0, "Bubble");
    qmlRegisterType<BubbleSeries>(uri, 1, 0, "BubbleSeries");
    qmlRegisterType<BubbleChart>(uri, 1, 0, "BubbleChart");
    qmlRegisterType<XYChart>(uri, 1, 0, "XYChart");
    qmlRegisterType<XYSeries>(uri, 1, 0, "XYSeries");
    qmlRegisterType<ChartPoint>(uri, 1, 0, "ChartPoint");
    qmlRegisterType<LineChart>(uri, 1, 0, "LineChart");
    qmlRegisterType<LineSeries>(uri, 1, 0, "LineSeries");
    qmlRegisterType<PolarArea>(uri, 1, 0, "PolarArea");
    qmlRegisterType<PolarAreaChart>(uri, 1, 0, "PolarAreaChart");
    qmlRegisterType<PolarRAxis>(uri, 1, 0, "PolarRAxis");
    qmlRegisterType<PieSlice>(uri, 1, 0, "PieSlice");
    qmlRegisterType<PieChart>(uri, 1, 0, "PieChart");
    qmlRegisterType<BarChart>(uri, 1, 0, "BarChart");
    qmlRegisterType<BarSeries>(uri, 1, 0, "BarSeries");
    qmlRegisterType<CategoryAxis>(uri, 1, 0, "CategoryAxis");
    qmlRegisterType<StandartAxis>(uri, 1, 0, "StandartAxis");
    qmlRegisterType<ChartPen>(uri, 1, 0, "ChartPen");
}


