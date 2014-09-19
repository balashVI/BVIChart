#ifndef ABSTRACTSERIES_H
#define ABSTRACTSERIES_H

#include <QQuickPaintedItem>

///
/// \brief Базовий клас усіх серій графіків
///
/// Містить основні властивості та функціонал властиві усім серіям графіків
///
class AbstractSeries : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit AbstractSeries(QQuickItem *parent = 0);

    ///Назва серії
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    ///Якщо FALSE сегмент не буде малюватися
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    void setEnabled(bool value);
    bool enabled() const;
    QString name() const;
    void setName(const QString & value);

protected:
    QString pName;
    bool pEnabled;

signals:
    ///Сигналізує про зміну назви серії
    void nameChanged();
    ///Сигналізує про зміну властивості enabled
    void enabledChanged();

public slots:

};

#endif // ABSTRACTSERIES_H
