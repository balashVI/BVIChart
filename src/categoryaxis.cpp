#include "categoryaxis.h"
#include <QFontMetrics>

CategoryAxis::CategoryAxis(QQuickItem *parent) :
    AbstractAxis(parent), widthOfMaxLabel{0}, pBarValueSpacing{3}, pBarDatasetSpacing{5}
{
}

int CategoryAxis::barDatasetSpacing() const
{
    return pBarDatasetSpacing;
}

void CategoryAxis::setBarDatasetSpacing(int value)
{
    pBarDatasetSpacing = value;
    emit barDatasetSpacingChanged();
}

int CategoryAxis::barValueSpacing() const
{
    return pBarValueSpacing;
}

void CategoryAxis::setBarValueSpacing(int value)
{
    pBarValueSpacing = value;
    emit barValueSpacingChanged();
}

const QList<QString> &CategoryAxis::labels() const
{
    return pLabels;
}

void CategoryAxis::setLabels(QList<QString> newLabels)
{
    pLabels = std::move(newLabels);
    calculateWidthOfMaxLabel();
    emit labelsChanged();
}

int CategoryAxis::getWidthOfMaxLabel()
{
    return widthOfMaxLabel;
}

void CategoryAxis::calculateWidthOfMaxLabel()
{
    int labelWidth;
    widthOfMaxLabel = 0;
    QFontMetrics fm = QFontMetrics(pLabelsFont->getFont());
    for(int i=0;i<pLabels.length();++i){
        labelWidth = fm.width(pLabels[i]);
        if(labelWidth > widthOfMaxLabel)
            widthOfMaxLabel = labelWidth;
    }
}
