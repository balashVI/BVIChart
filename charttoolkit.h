#ifndef CHARTTOOLKIT_H
#define CHARTTOOLKIT_H

#include<QFont>
#include <QVariant>

class ChartToolkit
{
public:
    ChartToolkit();

    static void variantMapToFont(QFont &font, QVariantMap &data);
};

#endif // CHARTTOOLKIT_H
