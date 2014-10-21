#include "barchart.h"

BarChart::BarChart(QQuickItem *parent) :
    AbstractChart(parent), pXAxis{this}, pYAxis{this}
{
    connect(this, SIGNAL(seriesChanged()), &pLegend, SLOT(updateLegend()));
    pLegend.setSeriesList((QList<AbstractSeries*>*)(&seriesList));
    pXAxis.setName("X");
}

QQmlListProperty<BarSeries> BarChart::series()
{
    return QQmlListProperty<BarSeries>(this, 0, &BarChart::appendSeries, &BarChart::seriesListLength,
                                       &BarChart::seriesAt, 0);
}

CategoryAxis *BarChart::xAxis()
{
    return &pXAxis;
}

StandartAxis *BarChart::yAxis()
{
    return &pYAxis;
}

void BarChart::appendSeries(QQmlListProperty<BarSeries> *seriesList, BarSeries *series)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if (chart) {
        series->setParentItem(chart);
        chart->seriesList.append(series);
        connect(series, SIGNAL(nameChanged()), &chart->pLegend, SLOT(updateLegend()));
        connect(series, SIGNAL(colorChanged()), &chart->pLegend, SLOT(updateLegend()));
        connect(series, SIGNAL(enabledChanged()), &chart->pLegend, SLOT(updateLegend()));
        connect(series, SIGNAL(dataChanged()), chart, SLOT(calculateNumbersOfCategories()));
        chart->calculateNumbersOfCategories();
        emit chart->seriesChanged();
    }
}

int BarChart::seriesListLength(QQmlListProperty<BarSeries> *seriesList)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.length();
    else return 0;
}

BarSeries *BarChart::seriesAt(QQmlListProperty<BarSeries> *seriesList, int index)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.at(index);
    return nullptr;
}

void BarChart::updateChildrenGeometry()
{
    pHeader.setPosition(QPoint((width()-pHeader.width())/2, pSpacing));
    //Визначення координат та розмірів дочірніх елементів
    switch (pLegend.location()) {
    case (ChartLegend::RightLocation):
        pLegend.recalculateSize(height()-3*pSpacing-pHeader.height());
        pLegend.setX(x()+width()-pSpacing-pLegend.width());
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);

        pXAxis.setX(pSpacing+pYAxis.calculateAxisLinePosition());
        pXAxis.setY(pLegend.y());
        pYAxis.setX(pSpacing);
        pYAxis.setY(pLegend.y());
        pYAxis.setWidth(width()-pLegend.width()-3*pSpacing);
        pXAxis.setSize(QSizeF(pYAxis.width()-pYAxis.calculateAxisLinePosition(),
                              height()-pHeader.height()-3*pSpacing));
        pYAxis.setHeight(pXAxis.calculateAxisLinePosition());
        break;
    case(ChartLegend::LeftLocation):
        pLegend.recalculateSize(height()-3*pSpacing-pHeader.height());
        pLegend.setX(pSpacing);
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);

        pYAxis.setX(pLegend.width()+2*pSpacing);
        pYAxis.setY(pLegend.y());
        pXAxis.setX(pYAxis.x()+pYAxis.calculateAxisLinePosition());
        pXAxis.setY(pLegend.y());
        pYAxis.setWidth(width()-pLegend.width()-3*pSpacing);
        pXAxis.setSize(QSizeF(pYAxis.width()-pYAxis.calculateAxisLinePosition(),
                              height()-pHeader.height()-3*pSpacing));
        pYAxis.setHeight(pXAxis.calculateAxisLinePosition());
        break;
    case(ChartLegend::TopLocation):
        pLegend.recalculateSize(width()-2*pSpacing);
        pLegend.setX(pSpacing);
        pLegend.setY(pHeader.y()+pHeader.height()+pSpacing);

        pYAxis.setX(pSpacing);
        pYAxis.setY(pLegend.y()+pLegend.height()+pSpacing);
        pXAxis.setX(pSpacing+pYAxis.calculateAxisLinePosition());
        pXAxis.setY(pYAxis.y());
        pYAxis.setWidth(width()-2*pSpacing);
        pXAxis.setSize(QSizeF(pYAxis.width()-pYAxis.calculateAxisLinePosition(),
                              height()-pLegend.y()-pLegend.height()-2*pSpacing));
        pYAxis.setHeight(pXAxis.calculateAxisLinePosition());
        break;
    case(ChartLegend::BottomLocation):
        pLegend.recalculateSize(width()-2*pSpacing);
        pLegend.setX(pSpacing);
        pLegend.setY(y()+height()-pSpacing-pLegend.height());

        pYAxis.setX(pSpacing);
        pYAxis.setY(pHeader.y()+pHeader.height()+pSpacing);
        pXAxis.setX(pSpacing+pYAxis.calculateAxisLinePosition());
        pXAxis.setY(pYAxis.y());
        pYAxis.setWidth(width()-2*pSpacing);
        pXAxis.setSize(QSizeF(pYAxis.width()-pYAxis.calculateAxisLinePosition(),
                              height()-pLegend.height()-pHeader.height()-4*pSpacing));
        pYAxis.setHeight(pXAxis.calculateAxisLinePosition());
        break;
    default:
        //Якщо легенда не відображається
        pLegend.recalculateSize(0);
        pYAxis.setX(pSpacing);
        pYAxis.setY(pHeader.y()+pHeader.height()+pSpacing);
        pXAxis.setX(pSpacing+pYAxis.calculateAxisLinePosition());
        pXAxis.setY(pYAxis.y());
        pYAxis.setWidth(width()-2*pSpacing);
        pXAxis.setSize(QSizeF(pYAxis.width()-pYAxis.calculateAxisLinePosition(),
                              height()-2*pSpacing));
        pYAxis.setHeight(pXAxis.calculateAxisLinePosition());
        break;
    }

    //Зміна розмірів серій
    for(int i=0;i<seriesList.length();++i){
        seriesList[i]->setPosition(QPointF(pXAxis.x(), pXAxis.y()));
        seriesList[i]->setSize(QSizeF(pXAxis.width(), pYAxis.height()));
    }
}

void BarChart::calculateNumbersOfCategories()
{
    int numberOfCategories{1};
    for(BarSeries* i: seriesList)
        if(numberOfCategories < i->data().length())
            numberOfCategories = i->data().length();
    pXAxis.setNumberOfCategories(numberOfCategories);
}
