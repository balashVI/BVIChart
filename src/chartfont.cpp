#include "chartfont.h"
#include <QDebug>
#include <QFontMetrics>

ChartFont::ChartFont(QObject *parent) :
    QObject(parent)
{
}

int ChartFont::getHeight()
{
    QFontMetrics metrics(font);
    return metrics.height();
}

/**
 * @brief
 *
 * Повертає посилання на змінну типу QFont, котра містить сукупні характеристики шрифту
 * @see QFont
 */
const QFont &ChartFont::getFont()
{
    return font;
}

void ChartFont::setPointSize(int value)
{
    font.setPointSize(value);
    emit pointSizeChanged();
    emit changed();
}

int ChartFont::pointSize() const
{
    return font.pointSize();
}

void ChartFont::setPixelSize(int value)
{
    font.setPixelSize(value);
    emit pixelSizeChanged();
    emit changed();
}

int ChartFont::pixelSize() const
{
    return font.pixelSize();
}

void ChartFont::setItalic(bool value)
{
    font.setItalic(value);
    emit italicChanged();
    emit changed();
}

bool ChartFont::italic() const
{
    return font.italic();
}

void ChartFont::setFamily(const QString &value)
{
    font.setFamily(value);
}

QString ChartFont::family() const
{
    return font.family();
}

bool ChartFont::bold() const
{
    return font.bold();
}

void ChartFont::setBold(bool value)
{
    font.setBold(value);
    emit boldChanged();
    emit changed();
}
