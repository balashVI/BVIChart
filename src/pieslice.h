#ifndef PIESLICE_H
#define PIESLICE_H

#include <QQuickItem>
#include <QColor>

/**
 * @brief Сегмент PieChart
 *
 * Інкапсулює властивості сегмента графіка PieChart
 */
class PieSlice : public QQuickItem
{
    Q_OBJECT
public:
    explicit PieSlice(QQuickItem *parent = 0);

    ///Задає числове значення сегмента
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

    ///Задає назву сегмента
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)

    ///Якщо FALSE сегмент не буде малюватися
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    ///Задає колір мегмента
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

    ///Задає колір сегмента у випадку коли він активний
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)

    void setHighlightColor(const QColor & value);
    const QColor& highlightColor() const;
    void setColor(const QColor& value);
    const QColor& color() const;
    void setEnabled(bool value);
    bool enabled() const;
    void setLabel(const QString &value);
    const QString& label() const;
    double value() const;
    void setValue(double value);

private:
    double pValue;
    QString pLabel;
    bool pEnabled;
    QColor pColor;
    QColor pHighlightColor;

signals:
    void changed();
    void valueChanged();
    void labelChanged();
    void enabledChanged();
    void colorChanged();
    void highlightColorChanged();

public slots:

};

#endif // PIESLICE_H
