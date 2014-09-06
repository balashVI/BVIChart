#include "chartpopup.h"
#include "charttoolkit.h"

ChartPopup::ChartPopup(QObject *parent) :
    QObject(parent), pPadding{6}, pEnabled{true}, pBackgroundColor{QColor(0,0,0,200)}, pTextColor{QColor(255,255,255)}
{
    pFont.setPointSize(11);
}

QFont ChartPopup::font() const
{
    return pFont;
}

int ChartPopup::padding() const
{
    return pPadding;
}

void ChartPopup::setPadding(int value)
{
    pPadding = value;
    emit changed();
    emit paddingChanged();
}

bool ChartPopup::enabled() const
{
    return pEnabled;
}

void ChartPopup::setEnabled(bool value)
{
    pEnabled = value;
    emit changed();
    emit enabledChanged();
}

QColor ChartPopup::backgroundColor() const
{
    return pBackgroundColor;
}

void ChartPopup::setBackgroundColor(QColor &value)
{
    pBackgroundColor = value;
    emit changed();
    emit backgroundColorChanged();
}

double ChartPopup::backgroundOpacity() const
{
    return pBackgroundColor.alpha()/255.0;
}

void ChartPopup::setBackgroundOpacity(double value)
{
    pBackgroundColor.setAlpha(value*255);
    emit changed();
    emit backgroundOpacityChanged();
}

QColor ChartPopup::textColor() const
{
    return pTextColor;
}

void ChartPopup::setTextColor(QColor &value)
{
    pTextColor=value;
    emit changed();
    emit textColorChanged();
}

void ChartPopup::changeFont(QVariantMap& value)
{
    ChartToolkit::variantMapToFont(pFont, value);
    emit changed();
    emit fontChanged();
}
