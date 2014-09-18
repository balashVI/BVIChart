#include "charttoolkit.h"

ChartToolkit::ChartToolkit()
{
}

void ChartToolkit::variantMapToFont(QFont &font, QVariantMap &data)
{
    if(data.contains("family"))
        font.setFamily(data.value("family").toString());
    if(data.contains("pixelSize"))
        font.setPixelSize(data.value("pixelSize").toInt());
}
