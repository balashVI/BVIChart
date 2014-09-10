#ifndef CHARTAXIS_H
#define CHARTAXIS_H

#include <QObject>
#include <QFont>
#include <QPen>

#include "charttoolkit.h"

class ChartAxis : public QObject
{
    Q_OBJECT
public:
    //*********************************************
    // Методи
    //*********************************************
    explicit ChartAxis(QObject *parent = 0);

    void setOrientation(int value);
    const QPen& getLinePen() const;
    void setLength(int value);
    int length() const;
    int labelHeight() const;
    void setMinMaxValues(double min, double max);
    int numberOfSteps() const;
    const QList<QString>& labels();
    int convertValue(double value) const;

    //*********************************************
    // Qml методи
    //*********************************************

    Q_INVOKABLE void changeFont(QVariantMap &value);

    //*********************************************
    // Qml властивості
    //*********************************************

    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool visibleLabels READ visibleLabels WRITE setVisibleLabels NOTIFY visibleLabelsChanged)
    Q_PROPERTY(QFont font READ font NOTIFY fontChanged)
    Q_PROPERTY(bool automated READ automated WRITE setAutomated NOTIFY automatedChanged)
    Q_PROPERTY(bool visibleLines READ visibleLines WRITE setVisibleLines NOTIFY visibleLinesChanged)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(double lineOpacity READ lineOpacity WRITE setLineOpacity NOTIFY lineOpacityChanged)
    Q_PROPERTY(Qt::PenStyle lineStyle READ lineStyle WRITE setLineStyle NOTIFY lineStyleChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(bool visibleLabelBackground READ visibleLabelBackground WRITE setVisibleLabelBackground NOTIFY visibleLabelBackgroundChanged)
    Q_PROPERTY(QColor labelBackgroundColor READ labelBackgroundColor WRITE setLabelBackgroundColor NOTIFY labelBackgroundColorChanged)
    Q_PROPERTY(double labelBackgroundOpacity READ labelBackgroundOpacity WRITE setLabelBackgroundOpacity NOTIFY labelBackgroundOpacityChanged)
    Q_PROPERTY(unsigned int labelPadding READ labelPadding WRITE setLabelPadding NOTIFY labelPaddingChanged)
    Q_PROPERTY(bool invert READ invert WRITE setInvert NOTIFY invertChanged)
    Q_PROPERTY(bool fixedMin READ fixedMin WRITE setFixedMin NOTIFY fixedMinChanged)
    Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(bool fixedMax READ fixedMax WRITE setFixedMax NOTIFY fixedMaxChanged)
    Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)

    void setMax(double value);
    double max() const;
    void setFixedMax(bool value);
    bool fixedMax() const;
    void setMin(double value);
    double min() const;
    void setFixedMin(bool value);
    bool fixedMin() const;
    void setInvert(bool value);
    bool invert() const;
    void setLabelPadding(unsigned int value);
    unsigned int labelPadding() const;
    void setLabelBackgroundOpacity(double value);
    double labelBackgroundOpacity() const;
    void setLabelBackgroundColor(QColor value);
    QColor labelBackgroundColor() const;
    void setVisibleLabelBackground(bool value);
    bool visibleLabelBackground() const;
    QColor textColor() const;
    void setTextColor(QColor &value);
    bool visible() const;
    void setVisible(bool value);
    bool visibleLabels() const;
    void setVisibleLabels(bool value);
    QFont font() const;
    bool automated() const;
    void setAutomated(bool value);
    bool visibleLines() const;
    void setVisibleLines(bool value);
    int lineWidth() const;
    void setLineWidth(int value);
    QColor lineColor() const;
    void setLineColor(QColor value);
    double lineOpacity() const;
    void setLineOpacity(double value);
    Qt::PenStyle lineStyle() const;
    void setLineStyle(Qt::PenStyle value);

    //*********************************************
    // Інше
    //*********************************************

    enum AxisOrientation { Vertical, Horizontal};

private:
    bool pVisible;
    bool pVisibleLabels;
    QFont pFont;
    bool pAutomated;
    bool pVisibleLines;
    QPen linePen;
    QColor pTextColor;
    bool pVisibleLabelBackground;
    QColor pLabelBackgroundColor;
    unsigned int pLabelPadding;
    bool pInvert;
    bool pFixedMin;
    bool pFixedMax;
    double pMin;
    double pMax;

    int mOrientation;
    int mLength;
    int mLabelHeight;
    double maxValue, minValue;
    int mNumberOfSteps;
    QList <QString> mLabels;
    double minPaintedValue;
    double maxPaintedValue;

    void update();
    double calculateOrderOfMagnitude(double value);

signals:
    void changed();
    void visibleChanged();
    void visibleLabelsChanged();
    void fontChanged();
    void automatedChanged();
    void visibleLinesChanged();
    void lineWidthChanged();
    void lineColorChanged();
    void lineOpacityChanged();
    void lineStyleChanged();
    void textColorChanged();
    void visibleLabelBackgroundChanged();
    void labelBackgroundColorChanged();
    void labelBackgroundOpacityChanged();
    void labelPaddingChanged();
    void invertChanged();
    void fixedMinChanged();
    void minChanged();
    void fixedMaxChanged();
    void maxChanged();

public slots:

};

#endif // CHARTAXIS_H
