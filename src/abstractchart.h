#ifndef ABSTRACTCHART_H
#define ABSTRACTCHART_H

#include <QQuickItem>
#include "chartheader.h"
#include "chartlegend.h"

/**
 * @brief Базовий клас усіх графіків
 *
 * Містить властивості та фінкції властиві усім графікам
 */
class AbstractChart : public QQuickItem
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit AbstractChart(QQuickItem *parent = 0);
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry) override;

    /// Ця властивість зберігає елемент заголовку графіка
    /// \see ChartHeader
    Q_PROPERTY(ChartHeader* header READ header NOTIFY headerChanged)

    /// Ця властивість зберігає легенду графіка
    /// \see ChartHeader
    Q_PROPERTY(ChartLegend* legend READ legend NOTIFY legendChanged)

    /// Ця вдастивість задає відстань між компонентами графіка
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)

    void setSpacing(int value);
    int spacing() const;
    ChartHeader *header();
    ChartLegend *legend();

protected:
    ChartHeader pHeader;
    ChartLegend pLegend;
    int pSpacing;

signals:
    void headerChanged();
    void legendChanged();
    void spacingChanged();

private slots:
    virtual void updateChildrenGeometry();
};

#endif // ABSTRACTCHART_H
