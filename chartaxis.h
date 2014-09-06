#ifndef CHARTAXIS_H
#define CHARTAXIS_H

#include <QObject>
#include <QFont>

#include "charttoolkit.h"

class ChartAxis : public QObject
{
    Q_OBJECT
public:
    explicit ChartAxis(QObject *parent = 0);

    Q_INVOKABLE void changeFont(QVariantMap &value);

    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool visibleLabels READ visibleLabels WRITE setVisibleLabels NOTIFY visibleLabelsChanged)
    Q_PROPERTY(QFont font READ font NOTIFY fontChanged)
    Q_PROPERTY(bool automated READ automated WRITE setAutomated NOTIFY automatedChanged)
    Q_PROPERTY(bool visibleLines READ visibleLines WRITE setVisibleLines NOTIFY visibleLinesChanged)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)

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

private:
    bool pVisible;
    bool pVisibleLabels;
    QFont pFont;
    bool pAutomated;
    bool pVisibleLines;
    int pLineWidth;
    void setLineWidth(int value);

signals:
    void changed();
    void visibleChanged();
    void visibleLabelsChanged();
    void fontChanged();
    void automatedChanged();
    void visibleLinesChanged();
    void lineWidthChanged();

public slots:

};

#endif // CHARTAXIS_H
