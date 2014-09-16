#include "chartheader.h"
#include <QPainter>
#include <QFontMetrics>
#include <QDebug>

ChartHeader::ChartHeader(QQuickItem *parent) :
    QQuickPaintedItem(parent), pTitle{"Chart"}, pFont{new ChartFont(this)}
{
    setAntialiasing(true);
    pFont->setPointSize(14);
    connect(pFont, SIGNAL(changed()), this, SLOT(recalculateSize()));
}

void ChartHeader::setFont(ChartFont *value)
{
    if(value){
        pFont->deleteLater();
        pFont=value;
        connect(pFont, SIGNAL(changed()), this, SLOT(recalculateSize()));
        recalculateSize();
        emit fontChanged();
    }
}

ChartFont *ChartHeader::font()
{
    return pFont;
}

const QString &ChartHeader::title() const
{
    return pTitle;
}

void ChartHeader::setTitle(const QString &value)
{
    pTitle = value;
    recalculateSize();
    emit titleChanged();
}

void ChartHeader::paint(QPainter *painter)
{
    painter->setFont(pFont->getFont());
    painter->drawText(contentsBoundingRect(), pTitle);
}

void ChartHeader::recalculateSize()
{
    QFontMetrics fMetrics(pFont->getFont());
    QRect contentRect = fMetrics.boundingRect(pTitle);
    setSize(QSize(contentRect.width(), contentRect.height()));
}
