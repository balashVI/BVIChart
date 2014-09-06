#include "chartcanvas.h"

ChartCanvas::ChartCanvas(QQuickItem *parent) :
    QQuickPaintedItem(parent), pPopup{new ChartPopup(this)}, pi{qAcos(-1)}, pPadding{7}, pPausePainting{false},
    pHoverEventsEnabled{true}
{
    setAcceptHoverEvents(true);

    connect(pPopup, SIGNAL(changed()), this, SLOT(update()));
}

int ChartCanvas::padding() const
{
    return pPadding;
}

void ChartCanvas::setPadding(int value)
{
    if(value<7)
        pPadding=7;
    else
        pPadding = value;
    update();
    emit paddingChanged();
}

bool ChartCanvas::pausePainting() const
{
    return pPausePainting;
}

void ChartCanvas::setPausePainting(bool value)
{
    pPausePainting = value;
    if(pPausePainting)
        setAcceptHoverEvents(false);
    else {
        setAcceptHoverEvents(pHoverEventsEnabled);
        update();
    }
    emit pausePaintingChanged();
}

bool ChartCanvas::hoverEventsEnabled() const
{
    return pHoverEventsEnabled;
}

void ChartCanvas::setHoverEventsEnabled(bool value)
{
    pHoverEventsEnabled = value;
    if(!pPausePainting)
        setAcceptHoverEvents(value);
    emit hoverEventsEnabledChanged();
}

ChartPopup *ChartCanvas::popup() const
{
    return pPopup;
}
