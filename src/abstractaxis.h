#ifndef ABSTRACTAXIS_H
#define ABSTRACTAXIS_H

#include <QQuickPaintedItem>
#include "chartpen.h"
#include "chartfont.h"

class AbstractAxis : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit AbstractAxis(QQuickItem *parent = 0);

    ///Містить користувацькі позначки осі
    Q_PROPERTY(QList<QString> labels READ labels WRITE setLabels NOTIFY labelsChanged)

    ///Містить налаштування лінії осі
    Q_PROPERTY(ChartPen* axisLine READ axisLine WRITE setAxisLine NOTIFY axisLineChanged)

    ///Містить налаштування основних ліній сітки
    Q_PROPERTY(ChartPen* majorLines READ majorLines WRITE setMajorLines NOTIFY majorLinesChanged)

    ///Містить налаштування допоміжних ліній сітки
    Q_PROPERTY(ChartPen* minorLines READ minorLines WRITE setMinorLines NOTIFY minorLinesChanged)

    ///Містить налаштування шрифту

    void setMinorLines(ChartPen* value);
    ChartPen* minorLines() const;
    void setMajorLines(ChartPen* value);
    ChartPen* majorLines() const;
    void setAxisLine(ChartPen* value);
    ChartPen* axisLine() const;
    void setLabels(QList<QString> in);
    const QList<QString> &labels() const;

protected:
    QList<QString> pLabels;
    ChartPen *pAxisPen, *pMajorLines, *pMinorLines;
    ChartFont *pFont;

signals:
    void labelsChanged();
    void axisLineChanged();
    void majorLinesChanged();
    void minorLinesChanged();

public slots:

};

#endif // ABSTRACTAXIS_H
