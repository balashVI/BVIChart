#ifndef BARCHART_H
#define BARCHART_H

#include "abstractchart.h"
#include "barseries.h"
#include "categoryaxis.h"

///
/// \brief Стовпчикова діаграма
///
/// Малює стовпчикову діаграму. Приклад використання:
/// \code
/// ...
/// BarChart{
///     anchors.fill: parent
///     series: [
///         BarSeries{
///         },
///         BarSeries{
///         }
///     ]
/// }
/// ...
/// \endcode
///
class BarChart : public AbstractChart
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit BarChart(QQuickItem *parent = 0);

    /// Зберігає список серій графіка
    ///
    /// Приклад ініціалізації:
    /// \code
    /// ...
    /// series: [
    ///     BarSeries{...},
    ///     BarSeries{...},
    ///     BarSeries{...}
    /// ]
    /// ...
    /// \endcode
    /// Отримати кількість елементів можна наступним чином:
    /// \code
    /// series.length
    /// \endcode
    /// Отримати доступ до i-тої серії в списку можна наступним чином:
    /// \code
    /// series[i]
    /// \endcode
    ///
    /// \see BarSeries
    Q_PROPERTY(QQmlListProperty<BarSeries> series READ series NOTIFY seriesChanged())
    QQmlListProperty<BarSeries> series();

    Q_PROPERTY(CategoryAxis* xAxis READ xAxis NOTIFY xAxisChanged)
    CategoryAxis* xAxis();

private:
    CategoryAxis pXAxis;

protected:
    static void appendSeries(QQmlListProperty<BarSeries> *seriesList, BarSeries *series);
    static int seriesListLength(QQmlListProperty<BarSeries> *seriesList);
    static BarSeries *seriesAt(QQmlListProperty<BarSeries> *seriesList, int index);
    QList<BarSeries *> seriesList;

signals:
    /// Сигналізує про зміну серій
    /// \see BarSeries
    void seriesChanged();
    void xAxisChanged();
private slots:
    void updateChildrenGeometry() override;
    void calculateNumbersOfCategories();
};

#endif // BARCHART_H
