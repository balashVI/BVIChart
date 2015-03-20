#ifndef PIECHART_H
#define PIECHART_H

#include "abstractchart.h"

///
/// \brief Кругова діаграма
///
/// Малює кругову діаграму. Приклад використання:
/// \code
/// ...
/// PieChart{
///     anchors.fill: parent
///     series: [
///         PieSeries{
///         },
///         PieSeries{
///         }
///     ]
/// }
/// ...
/// \endcode
///
class PieChart : public AbstractChart
{
    Q_OBJECT
public:
    explicit PieChart(QQuickPaintedItem *parent = 0);

signals:

public slots:

};

#endif // PIECHART_H
