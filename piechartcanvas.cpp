#include "piechartcanvas.h"
#include <QDebug>

PieChartCanvas::PieChartCanvas(QQuickItem *parent)
    : ChartCanvas(parent), pStrokeVisible{true}, pStrokeWidth{3}, pStrokeColor{QColor(255,255,255)}, pCurrentSlice{-1},
      pAngleOffset{0}
{
    setObjectName("PieChartCanvas");
}

void PieChartCanvas::paint(QPainter *painter)
{
    if(!pPausePainting){
        painter->setRenderHints(QPainter::Antialiasing, true);

        //Обчислення області для малювання
        QRectF fillRect = contentsBoundingRect();
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
        double beginAngle = pAngleOffset;
        double segmentAngle;
        int counter{-1};
        for (auto &i: slices) {
            ++counter;
            if(!i.enabled)
                continue;
            segmentAngle = (i.value/sumSlicesValue) * 5760;
            if(counter == pCurrentSlice){
                //Виділення активного сегмента
                painter->setBrush(QBrush(i.color.lighter(125)));
                painter->drawPie(QRectF(fillRect.x()-7, fillRect.y()-7, fillRect.width()+14, fillRect.height()+14), beginAngle, segmentAngle);
                painter->drawArc(fillRect, beginAngle, segmentAngle);

                //Обчислення даних для вспливаючої підказки
                if(pPopup->enabled()){
                    phi = ((int)(beginAngle + segmentAngle/2)%5760)/16;
                    popupTxt = i.label+": "+QString::number(i.value);
                }

            } else {
                painter->setBrush(QBrush(i.color));
                painter->drawPie(fillRect, beginAngle, segmentAngle);
            }
            beginAngle += segmentAngle;
        }

        //Малювання вспливаючої підказки
        if(pPopup->enabled() && pCurrentSlice!=-1){
            int popupPadding = pPopup->padding();
            painter->setFont(pPopup->font());
            QRect popupTextRect = painter->fontMetrics().boundingRect(popupTxt);
            QPoint popupPoint;
            QPoint popupCenterBottomPoint;
            int r = fillRect.width()/4.0;
            popupCenterBottomPoint.setX(fillRect.center().x()+r*qCos(phi*pi/180.0));
            popupCenterBottomPoint.setY(fillRect.center().y()-r*qSin(phi*pi/180.0));
            popupPoint.setX(popupCenterBottomPoint.x() - popupTextRect.width()/2-popupPadding);
            popupPoint.setY(popupCenterBottomPoint.y() - popupTextRect.height()-2*popupPadding-9);

            painter->setBrush(QBrush(pPopup->backgroundColor()));
            painter->setPen(QPen(QColor(0,0,0,0)));
            painter->drawRoundedRect(popupPoint.x(), popupPoint.y(), popupTextRect.width()+2*popupPadding,
                                     popupTextRect.height()+2*popupPadding, 5, 5);
            QPainterPath triangle;
            triangle.moveTo(popupCenterBottomPoint);
            triangle.lineTo(popupCenterBottomPoint.x()-10, popupCenterBottomPoint.y()-9);
            triangle.lineTo(popupCenterBottomPoint.x()+10, popupCenterBottomPoint.y()-9);
            triangle.lineTo(popupCenterBottomPoint);
            painter->drawPath(triangle);
            painter->setPen(QPen(pPopup->textColor()));
            painter->drawText(popupPoint.x()+popupPadding, popupPoint.y()+popupPadding-popupTextRect.y(), popupTxt);
        }
    }
}

void PieChartCanvas::hoverMoveEvent(QHoverEvent *event)
{
    QRectF rect = contentsBoundingRect();
    QPoint center(rect.x()+rect.width()/2, rect.y()+rect.height()/2);
    QPointF X = event->posF();
    double a = qFabs(X.y()-center.y());
    double b = qSqrt((X.x()-center.x())*(X.x()-center.x())+((X.y()-center.y())*(X.y()-center.y())));
    double radius = (rect.width()>rect.height())?rect.height()/2:rect.width()/2;
    if(b > radius){
        if(pCurrentSlice != -1){
            setCurrentItem(-1);
            update();
            emit hoverSliceChanged();
        }
        return;
    }
    double alpha = qAsin(a/b)*180.0/pi;
    if(X.x()>center.x()){
        if(X.y()>center.y())
            alpha = 360 - alpha;
    } else {
        if(X.y()>center.y())
            alpha += 180;
        else
            alpha = 180 - alpha;
    }
    int angle = 0;
    alpha = (int)(alpha - pAngleOffset/16) % 360;
    if(alpha<0)
        alpha = 360+alpha;
    int counter{-1};
    for(auto &i: slices){
        ++counter;
        if(!i.enabled)
            continue;
        angle += (i.value/sumSlicesValue) * 360;
        if(alpha<angle){
            if(counter != pCurrentSlice){
                setCurrentItem(counter);
                update();
                emit hoverSliceChanged();
            }
            break;
        }
    }
}

void PieChartCanvas::addSlice(QVariantMap data)
{
    pieSlice slice;
    if(data.contains("value"))
        slice.value = data.value("value").toDouble();
    if(data.contains("label"))
        slice.label = data.value("label").toString();
    if(data.contains("color"))
        slice.color = data.value("color").toString();
    if(data.contains("enabled"))
        slice.enabled = data.value("enabled").toBool();
    slices.append(slice);
    emit slicesChanged();
    sliceChanged();
}

bool PieChartCanvas::setSliceProperty(int sliceIndex, QVariantMap data)
{
    if((sliceIndex >= 0) && (sliceIndex < slices.length())){
        if(data.contains("value"))
            slices[sliceIndex].value = data.value("value").toDouble();
        if(data.contains("label"))
            slices[sliceIndex].label = data.value("label").toString();
        if(data.contains("color"))
            slices[sliceIndex].color = data.value("color").toString();
        if(data.contains("enabled"))
            slices[sliceIndex].enabled = data.value("enabled").toBool();

        emit slicesChanged();
        sliceChanged();
        return true;
    } else
        return false;
}

bool PieChartCanvas::moveSlice(int from, int to)
{
    if((from >= 0) && (from < slices.length()) && (to >= 0) && (to < slices.length())){
        slices.move(from, to);
        emit slicesChanged();
        sliceChanged();
        return true;
    } else
        return false;
}

int PieChartCanvas::numberOfSlices()
{
    return slices.length();
}

bool PieChartCanvas::removeSlice(int index)
{
    if((index >= 0) && (index < slices.length())){
        slices.removeAt(index);
        sliceChanged();
        emit slicesChanged();
        return true;
    } else
        return false;
}

void PieChartCanvas::removeAllSlices()
{
    slices.clear();
    emit slicesChanged();


}

QVariantMap PieChartCanvas::getSlice(int index)
{
    QVariantMap res;
    if((index >= 0) && (index < slices.length())){
        res.insert("label", slices.at(index).label);
        res.insert("value", slices.at(index).value);
        res.insert("color", slices.at(index).color);
        res.insert("enabled", slices.at(index).enabled);
    }
    return res;
}

QVariantList PieChartCanvas::getLegend()
{
    QVariantList list;
    QVariantMap map;
    for(auto &i: slices){
        map.clear();
        map.insert("label", i.label);
        map.insert("color", i.color);
        map.insert("enabled", i.enabled);
        list.append(map);
    }
    return list;
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
    if(value>=0 && value<slices.length() && slices.at(value).enabled){
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

void PieChartCanvas::sliceChanged()
{
    sumSlicesValue = 0;
    for(auto &i: slices)
        if(i.enabled)
            sumSlicesValue += i.value;
    if(acceptHoverEvents()){
        if(pCurrentSlice != -1)
            setCurrentItem(-1);
    }
    update();
}
