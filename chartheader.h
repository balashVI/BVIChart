#ifndef ChartHeader_H
#define ChartHeader_H

#include <QQuickPaintedItem>
#include "chartfont.h"

class ChartHeader : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit ChartHeader(QQuickItem *parent = 0);

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(ChartFont* font READ font WRITE setFont NOTIFY fontChanged)

    void setFont(ChartFont* value);
    ChartFont* font();
    const QString& title() const;
    void setTitle(const QString& value);

private:
    virtual void paint(QPainter *painter);

    QString pTitle;
    ChartFont *pFont;

signals:
    void titleChanged();
    void fontChanged();

private slots:
    void recalculateSize();
};

#endif // ChartHeader_H
