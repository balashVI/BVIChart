#include "xyseries.h"

XYSeries::XYSeries(QObject *parent):
    AbstractSeries(parent), pStrokePen{new ChartPen(this)}, pDrawPoints{true}
{
    pStrokePen->setWidth(3);
}

XYSeries::~XYSeries()
{

}

QQmlListProperty<ChartPoint> XYSeries::data()
{
    return QQmlListProperty<ChartPoint>(this, 0, &XYSeries::appendPoint, &XYSeries::dataListLength,
                                        &XYSeries::pointAt, 0);
}

ChartPen *XYSeries::strokePen() const
{
    return pStrokePen;
}

void XYSeries::setStrokePen(ChartPen *value)
{
    if(value){
        pStrokePen->deleteLater();
        pStrokePen=value;
        emit strokePenChanged();
    }
}

bool XYSeries::drawPoints() const
{
    return pDrawPoints;
}

void XYSeries::getDataRange(double &xLoverValue, double &xUpperValue, double &yLoverValue, double &yUpperValue)
{
    xLoverValue = this->xLoverValue;
    xUpperValue = this->xUpperValue;
    yLoverValue = this->yLoverValue;
    yUpperValue = this->yUpperValue;
}

const QList<ChartPoint *> *XYSeries::getDataList()
{
    return &dataList;
}

void XYSeries::appendPoint(QQmlListProperty<ChartPoint> *dataList, ChartPoint *point)
{
    XYSeries *series = qobject_cast<XYSeries *>(dataList->object);
    if (series) {
        point->setParent(series);
        series->dataList.append(point);
        connect(point, &ChartPoint::xChanged, series, &XYSeries::calculateDataRange);
        connect(point, &ChartPoint::yChanged, series, &XYSeries::calculateDataRange);
        series->calculateDataRange();
        emit series->dataChanged();
    }
}

int XYSeries::dataListLength(QQmlListProperty<ChartPoint> *dataList)
{
    XYSeries *series = qobject_cast<XYSeries *>(dataList->object);
    if (series) {
        return series->dataList.length();
    } else
        return 0;
}

ChartPoint *XYSeries::pointAt(QQmlListProperty<ChartPoint> *dataList, int index)
{
    XYSeries *series = qobject_cast<XYSeries *>(dataList->object);
    if (series) {
        return series->dataList.at(index);
    } else return nullptr;
}

void XYSeries::calculateDataRange()
{
    xUpperValue = std::numeric_limits<int>::min();
    xLoverValue = std::numeric_limits<int>::max();
    yUpperValue = std::numeric_limits<int>::min();
    yLoverValue = std::numeric_limits<int>::max();

    for(ChartPoint *i: dataList){
        if(i->x()>xUpperValue)
            xUpperValue = i->x();
        if(i->x()<xLoverValue)
            xLoverValue = i->x();
        if(i->y()>yUpperValue)
            yUpperValue = i->y();
        if(i->x()<yLoverValue)
            yLoverValue = i->y();
    }
}

void XYSeries::setDrawPoints(bool value)
{
    pDrawPoints = value;
    emit drawPointsChanged();
}
