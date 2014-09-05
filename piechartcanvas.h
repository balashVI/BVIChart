#ifndef PieChartCanvas_H
#define PieChartCanvas_H

#include "chartcanvas.h"

class PieChartCanvas : public ChartCanvas
{
    Q_OBJECT

public:
    PieChartCanvas(QQuickItem *parent = 0);

    Q_INVOKABLE void addSlice(QVariantMap data);
    Q_INVOKABLE bool setSliceProperty(int sliceIndex, QVariantMap data);
    Q_INVOKABLE bool moveSlice(int from, int to);
    Q_INVOKABLE int numberOfSlices();
    Q_INVOKABLE bool removeSlice(int index);
    Q_INVOKABLE void removeAllSlices();
    Q_INVOKABLE QVariantMap getSlice(int index);
    Q_INVOKABLE QVariantList getLegend();

    Q_PROPERTY(bool strokeVisible READ strokeVisible WRITE setStrokeVisible NOTIFY strokeVisibleChanged)
    bool strokeVisible() const;
    void setStrokeVisible(bool value);

    Q_PROPERTY(int strokeWidth READ strokeWidth WRITE setStrokeWidth NOTIFY strokeWidthChanged)
    int strokeWidth() const;
    void setStrokeWidth(int value);

    Q_PROPERTY(QColor strokeColor READ strokeColor WRITE setStrokeColor NOTIFY strokeColorChanged)
    QColor strokeColor() const;
    void setStrokeColor(QColor value);

    Q_PROPERTY(int currentItem READ currentItem WRITE setCurrentItem NOTIFY currentItemChanged)
    int currentItem() const;
    void setCurrentItem(int value);

    Q_PROPERTY(int angleOffset READ angleOffset WRITE setAngleOffset NOTIFY angleOffsetChanged)
    int angleOffset() const;
    void setAngleOffset(int value);



private:
    void paint(QPainter *painter);
    void hoverMoveEvent(QHoverEvent * event);

    struct pieSlice{
        QString label;
        double value;
        QColor color;
        bool enabled;
        pieSlice(){
            label = "Slice";
            value = 1;
            color = QColor("gray");
            enabled = true;
        }
    };

    QList <pieSlice> slices;
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
    void slotSliceChanged();
};

#endif // PieChartCanvas_H

