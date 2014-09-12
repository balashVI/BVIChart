#include "piechartcanvas.h"
#include <QDebug>

PieChartCanvas::PieChartCanvas(QQuickItem *parent)
    : ChartCanvas(parent), pStrokeVisible{true}, pStrokeWidth{3}, pStrokeColor{QColor(255,255,255)}, pCurrentSlice{-1},
      pAngleOffset{0}
{
    setObjectName("PieChartCanvas");
    emit slicesChanged();
}



void PieChartCanvas::paint(QPainter *painter)
{
    if(!pPausePainting){
        painter->setRenderHints(QPainter::Antialiasing, true);

        //Обчислення області для малювання
        QRectF fillRect {contentsBoundingRect()};
        if(fillRect.height() > fillRect.width()){
            fillRect.setX(fillRect.x() + pPadding + pStrokeWidth);
            fillRect.setY(fillRect.y() + (fillRect.height()-fillRect.width())/2+pPadding);
            fillRect.setWidth(fillRect.width() - pPadding - pStrokeWidth);
            fillRect.setHeight(fillRect.width());
        } else {
            fillRect.setY(fillRect.y() + pPadding + pStrokeWidth);
            fillRect.setX(fillRect.x() + (fillRect.width()-fillRect.height())/2+pPadding);
            fillRect.setHeight(fillRect.height() - pPadding - pStrokeWidth);
            fillRect.setWidth(fillRect.height());
        }

        if(pStrokeVisible){
            QPen pen(pStrokeColor);
            pen.setWidth(pStrokeWidth);
            painter->setPen(pen);
        } else
            painter->setPen(QPen(QColor(0,0,0,0)));

        //Змінні для вспливаючих підказок
        int phi = 0;
        QString popupTxt;

        //Малювання сегментів
        int beginAngle {pAngleOffset};
        int segmentAngle;
        int counter{-1};
        for (PieSlice *i: mSlices) {
            ++counter;
            if(i->enabled()){
                segmentAngle = (i->value()/sumSlicesValue) * 5760;
                if(counter == pCurrentSlice){
                    //Виділення активного сегмента
                    painter->setBrush(QBrush(i->highlightColor()));
                    painter->drawPie(QRectF(fillRect.x()-7, fillRect.y()-7, fillRect.width()+14, fillRect.height()+14), beginAngle, segmentAngle);
                    painter->drawArc(fillRect, beginAngle, segmentAngle);

                    //Обчислення даних для вспливаючої підказки
                    if(pPopup->enabled()){
                        phi = ((int)(beginAngle + segmentAngle/2)%5760)/16;
                        popupTxt = i->label()+": "+QString::number(i->value());
                    }

                } else {
                    painter->setBrush(QBrush(i->color()));
                    painter->drawPie(fillRect, beginAngle, segmentAngle);
                }
                beginAngle += segmentAngle;
            }
        }

        //Малювання вспливаючої підказки
        if(pPopup->enabled() && pCurrentSlice!=-1){
            painter->setFont(pPopup->font());
            QRectF popupTextRect{painter->fontMetrics().boundingRect(popupTxt)};
            popupTextRect += QMargins(pPopup->padding(), pPopup->padding(), pPopup->padding(), pPopup->padding());
            int r = fillRect.width()/4.0;
            QPointF popupPoint {QPointF(fillRect.center().x()+r*qCos(phi*pi/180.0), fillRect.center().y()-r*qSin(phi*pi/180.0))};
            popupTextRect.moveCenter(QPointF(popupPoint.x(), popupPoint.y()-popupTextRect.height()/2-9));

            painter->setBrush(QBrush(pPopup->backgroundColor()));
            painter->setPen(QPen(QColor(0,0,0,0)));
            painter->drawRoundedRect(popupTextRect, 5, 5);
            QPainterPath triangle;
            triangle.moveTo(popupPoint);
            triangle.lineTo(popupPoint.x()-10, popupPoint.y()-9);
            triangle.lineTo(popupPoint.x()+10, popupPoint.y()-9);
            triangle.lineTo(popupPoint);
            painter->drawPath(triangle);
            painter->setPen(QPen(pPopup->textColor()));
            painter->drawText(popupTextRect, Qt::AlignHCenter | Qt::AlignVCenter, popupTxt);
        }
    }
}

void PieChartCanvas::hoverMoveEvent(QHoverEvent *event)
{
    QRectF rect {contentsBoundingRect()};
    QPointF center(rect.center());
    QPointF X {event->posF()};
    double a {qFabs(X.y()-center.y())};
    double b {qSqrt((X.x()-center.x())*(X.x()-center.x())+((X.y()-center.y())*(X.y()-center.y())))};
    double radius = (rect.width()>rect.height())?rect.height()/2:rect.width()/2;

    if(b > radius){
        if(pCurrentSlice != -1){
            setCurrentItem(-1);
            emit hoverSliceChanged();
        }
        return;
    }
    double alpha {qAsin(a/b)*180.0/pi};
    if(X.x()>center.x()){
        if(X.y()>center.y())
            alpha = 360 - alpha;
    } else {
        if(X.y()>center.y())
            alpha += 180;
        else
            alpha = 180 - alpha;
    }
    int angle {0};
    alpha = (int)(alpha - pAngleOffset/16) % 360;
    if(alpha<0)
        alpha = 360+alpha;
    int counter{-1};
    for(PieSlice* i: mSlices){
        ++counter;
        if(i->enabled()){
            angle += (i->value()/sumSlicesValue) * 360;
            if(alpha<angle){
                if(counter != pCurrentSlice){
                    setCurrentItem(counter);
                    emit hoverSliceChanged();
                }
                break;
            }
        }
    }
}

void PieChartCanvas::addSlice(QVariantMap data)
{
    PieSlice *slice = new PieSlice(this);
    if(data.contains("value"))
        slice->setValue(data.value("value").toDouble());
    if(data.contains("label"))
        slice->setLabel(data.value("label").toString());
    if(data.contains("color"))
        slice->setColor(data.value("color").toString());
    if(data.contains("highlightColor"))
        slice->setHighlightColor(data.value("highlightColor").toString());
    if(data.contains("enabled"))
        slice->setEnabled(data.value("enabled").toBool());
    mSlices.append(slice);
    connect(slice, &PieSlice::changed, this, &PieChartCanvas::someSliceChanged);
    sliceChanged();
}

bool PieChartCanvas::moveSlice(int from, int to)
{
    if((from >= 0) && (from < mSlices.length()) && (to >= 0) && (to < mSlices.length())){
        mSlices.move(from, to);
        sliceChanged();
        return true;
    } else
        return false;
}

bool PieChartCanvas::removeSlice(int index)
{
    if((index >= 0) && (index < mSlices.length())){
        mSlices.at(index)->deleteLater();
        mSlices.removeAt(index);
        sliceChanged();
        return true;
    } else
        return false;
}

void PieChartCanvas::removeAllSlices()
{
    for(PieSlice *i: mSlices)
        i->deleteLater();
    mSlices.clear();
    emit slicesChanged();
}

QVariantList PieChartCanvas::getLegend()
{
    QVariantList list;
    QVariantMap map;
    for(PieSlice*i: mSlices){
        map.clear();
        map.insert("label", i->label());
        map.insert("color", i->color());
        map.insert("enabled", i->enabled());
        list.append(map);
    }
    return list;
}

QQmlListProperty<PieSlice> PieChartCanvas::slices()
{
    return QQmlListProperty<PieSlice>(this, 0, &PieChartCanvas::appendSlice, &PieChartCanvas::slicesLength,
                                      &PieChartCanvas::sliceAt, 0);
}

bool PieChartCanvas::strokeVisible() const
{
    return pStrokeVisible;
}

void PieChartCanvas::setStrokeVisible(bool value)
{
    pStrokeVisible = value;
    update();
    emit strokeVisibleChanged();
}

int PieChartCanvas::strokeWidth() const
{
    return pStrokeWidth;
}

void PieChartCanvas::setStrokeWidth(int value)
{
    pStrokeWidth = value;
    update();
    emit strokeWidthChanged();
}

QColor PieChartCanvas::strokeColor() const
{
    return pStrokeColor;
}

void PieChartCanvas::setStrokeColor(QColor value)
{
    pStrokeColor = value;
    update();
    emit strokeColorChanged();
}

int PieChartCanvas::currentItem() const
{
    return pCurrentSlice;
}

void PieChartCanvas::setCurrentItem(int value)
{
    if(value>=0 && value<mSlices.length() && mSlices.at(value)->enabled()){
        pCurrentSlice = value;
        update();
        emit currentItemChanged();
        return;
    } else if(pCurrentSlice!=-1){
        pCurrentSlice = -1;
        update();
        emit currentItemChanged();
    }
}

int PieChartCanvas::angleOffset() const
{
    return pAngleOffset;
}

void PieChartCanvas::setAngleOffset(int value)
{
    value = value % 360;
    pAngleOffset = value*16;
    update();
    emit angleOffsetChanged();
}

void PieChartCanvas::appendSlice(QQmlListProperty<PieSlice> *slices, PieSlice *slice)
{
    PieChartCanvas *chart = qobject_cast<PieChartCanvas *>(slices->object);
    if (chart) {
        slice->setParent(chart);
        connect(slice, &PieSlice::changed, chart, &PieChartCanvas::someSliceChanged);
        chart->mSlices.append(slice);
        chart->sliceChanged();
    }
}

int PieChartCanvas::slicesLength(QQmlListProperty<PieSlice> *slices)
{
    PieChartCanvas *chart = qobject_cast<PieChartCanvas *>(slices->object);
    if(chart)
        return chart->mSlices.length();
    else return 0;
}

PieSlice *PieChartCanvas::sliceAt(QQmlListProperty<PieSlice> *slices, int index)
{
    PieChartCanvas *chart = qobject_cast<PieChartCanvas *>(slices->object);
    if(chart)
        return chart->mSlices.at(index);
    return nullptr;
}

void PieChartCanvas::sliceChanged()
{
    sumSlicesValue = 0;
    for(PieSlice *i: mSlices)
        if(i->enabled())
            sumSlicesValue += i->value();
    if(acceptHoverEvents()){
        if(pCurrentSlice != -1)
            setCurrentItem(-1);
    }
    emit slicesChanged();
    update();
}

void PieChartCanvas::someSliceChanged()
{
    sliceChanged();
}
