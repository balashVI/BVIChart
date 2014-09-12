#ifndef PieChartCanvas_H
#define PieChartCanvas_H

#include "chartcanvas.h"
#include "pieslice.h"
#include <QQmlListProperty>

class PieChartCanvas : public ChartCanvas
{
    Q_OBJECT

public:
    PieChartCanvas(QQuickItem *parent = 0);

    Q_INVOKABLE void addSlice(QVariantMap data);
    Q_INVOKABLE bool moveSlice(int from, int to);
    Q_INVOKABLE void removeAllSlices();
    Q_INVOKABLE bool removeSlice(int index);
    Q_INVOKABLE QVariantList getLegend();

    Q_PROPERTY(bool strokeVisible READ strokeVisible WRITE setStrokeVisible NOTIFY strokeVisibleChanged)
    Q_PROPERTY(int strokeWidth READ strokeWidth WRITE setStrokeWidth NOTIFY strokeWidthChanged)
    Q_PROPERTY(QColor strokeColor READ strokeColor WRITE setStrokeColor NOTIFY strokeColorChanged)
    Q_PROPERTY(int currentItem READ currentItem WRITE setCurrentItem NOTIFY currentItemChanged)
    Q_PROPERTY(int angleOffset READ angleOffset WRITE setAngleOffset NOTIFY angleOffsetChanged)
    Q_PROPERTY(QQmlListProperty<PieSlice> slices READ slices NOTIFY slicesChanged())
    QQmlListProperty<PieSlice> slices();

    bool strokeVisible() const;
    void setStrokeVisible(bool value);
    int strokeWidth() const;
    void setStrokeWidth(int value);
    QColor strokeColor() const;
    void setStrokeColor(QColor value);
    int currentItem() const;
    void setCurrentItem(int value);
    int angleOffset() const;
    void setAngleOffset(int value);

protected:
    static void appendSlice(QQmlListProperty<PieSlice> *slices, PieSlice *slice);
    static int slicesLength(QQmlListProperty<PieSlice> *slices);
    static PieSlice *sliceAt(QQmlListProperty<PieSlice> *slices, int index);
    QList<PieSlice *> mSlices;

    virtual void paint(QPainter *painter);
    virtual void hoverMoveEvent(QHoverEvent * event);
    virtual void sliceChanged();

    double sumSlicesValue;

    bool pStrokeVisible;
    int pStrokeWidth;
    QColor pStrokeColor;
    int pCurrentSlice;
    int pAngleOffset;

signals:
    void slicesChanged();
    void strokeVisibleChanged();
    void strokeWidthChanged();
    void strokeColorChanged();
    void currentItemChanged();
    void hoverSliceChanged();
    void angleOffsetChanged();

private slots:
    void someSliceChanged();

};

#endif // PieChartCanvas_H

