#ifndef CHARTFONT_H
#define CHARTFONT_H

#include <QObject>
#include <QFont>

class ChartFont : public QObject
{
    Q_OBJECT
public:
    explicit ChartFont(QObject *parent = 0);

    Q_INVOKABLE const QFont& getFont();

    Q_PROPERTY(bool bold READ bold WRITE setBold NOTIFY boldChanged)
    Q_PROPERTY(QString family READ family WRITE setFamily NOTIFY familyChanged)
    Q_PROPERTY(bool italic READ italic WRITE setItalic NOTIFY italicChanged)
    Q_PROPERTY(int pixelSize READ pixelSize WRITE setPixelSize NOTIFY pixelSizeChanged)
    Q_PROPERTY(int pointSize READ pointSize WRITE setPointSize NOTIFY pointSizeChanged)

    void setPointSize(int value);
    int pointSize() const;
    void setPixelSize(int value);
    int pixelSize() const;
    void setItalic(bool value);
    bool italic() const;
    void setFamily(const QString& value);
    QString family() const;
    bool bold() const;
    void setBold(bool value);

private:
    QFont font;

signals:
    void boldChanged();
    void familyChanged();
    void italicChanged();
    void pixelSizeChanged();
    void pointSizeChanged();
    void changed();

public slots:

};

#endif // CHARTFONT_H
