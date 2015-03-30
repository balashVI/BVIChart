#ifndef ABSTRACTAXIS_H
#define ABSTRACTAXIS_H

#include <QQuickItem>
#include "chartpen.h"
#include "chartfont.h"

class AbstractAxis : public QQuickItem
{
    Q_OBJECT
public:
    explicit AbstractAxis(QQuickItem *parent = 0);

    ///Містить користувацькі позначки осі
    Q_PROPERTY(QList<QString> labels READ labels WRITE setLabels NOTIFY labelsChanged)

    ///Містить налаштування лінії осі
    Q_PROPERTY(ChartPen* axisLine READ axisLine WRITE setAxisLine NOTIFY axisLineChanged)

    ///Містить налаштування ліній сітки
    Q_PROPERTY(ChartPen* gridLines READ gridLines WRITE setGridLines NOTIFY gridLinesChanged)

    ///Містить налаштування шрифту міток осі
    Q_PROPERTY(ChartFont* labelsFont READ labelsFont WRITE setLabelsFont NOTIFY labelsFontChanged)

    ///Містить назву осі
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    ///Містить налаштування фону назви осі
    Q_PROPERTY(ChartFont* nameFont READ nameFont WRITE setNameFont NOTIFY nameFontChanged)

    ///Керує відображенням назви осі
    Q_PROPERTY(bool nameVisible READ nameVisible WRITE setNameVisible NOTIFY nameVisibleChanged)

    ///Містить колір назви осі
    Q_PROPERTY(QColor nameColor READ nameColor WRITE setNameColor NOTIFY nameColorChanged)

    ///Вмикає/вимикає відображення підписів осі
    Q_PROPERTY(bool labelsVisible READ labelsVisible WRITE setLabelsVisible NOTIFY labelsVisibleChanged)

    void setLabelsVisible(bool value);
    bool labelsVisible() const;
    void setNameColor(const QColor& value);
    const QColor& nameColor() const;
    void setNameVisible(bool value);
    bool nameVisible() const;
    void setNameFont(ChartFont* value);
    ChartFont* nameFont() const;
    const QString& name() const;
    void setName(QString value);
    void setLabelsFont(ChartFont* value);
    ChartFont* labelsFont() const;
    void setGridLines(ChartPen* value);
    ChartPen* gridLines() const;
    void setAxisLine(ChartPen* value);
    ChartPen* axisLine() const;
    void setLabels(QList<QString> in);
    const QList<QString> &labels() const;

protected:
    QList<QString> pLabels;
    ChartPen *pAxisPen, *pGridLines;
    ChartFont *pLabelsFont, *pNameFont;
    QString pName;
    bool pNameVisible, pLabelsVisible;
    QColor pNameColor;
    int min(int a, int b);

signals:
    void labelsChanged();
    void axisLineChanged();
    void gridLinesChanged();
    void labelsFontChanged();
    void nameChanged();
    void nameFontChanged();
    void nameVisibleChanged();
    void nameColorChanged();
    void labelsVisibleChanged();

public slots:

};

#endif // ABSTRACTAXIS_H
