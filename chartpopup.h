#ifndef CHARTPOPUP_H
#define CHARTPOPUP_H

#include <QObject>
#include <QFont>
#include <QColor>

class ChartPopup : public QObject
{
    Q_OBJECT
public:
    explicit ChartPopup(QObject *parent = 0);

    Q_INVOKABLE void changeFont(QVariantMap &value);

    Q_PROPERTY(QFont font READ font NOTIFY fontChanged)
    Q_PROPERTY(int padding READ padding WRITE setPadding NOTIFY paddingChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(double backgroundOpacity READ backgroundOpacity WRITE setBackgroundOpacity NOTIFY backgroundOpacityChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

    QFont font() const;
    int padding() const;
    void setPadding(int value);
    bool enabled() const;
    void setEnabled(bool value);
    QColor backgroundColor() const;
    void setBackgroundColor(QColor &value);
    double backgroundOpacity() const;
    void setBackgroundOpacity(double value);
    QColor textColor() const;
    void setTextColor(QColor &value);

private:
    QFont pFont;
    int pPadding;
    bool pEnabled;
    QColor pBackgroundColor;
    QColor pTextColor;

signals:
    void fontChanged();
    void paddingChanged();
    void enabledChanged();
    void backgroundColorChanged();
    void backgroundOpacityChanged();
    void textColorChanged();
    void changed();
};

#endif // CHARTPOPUP_H
