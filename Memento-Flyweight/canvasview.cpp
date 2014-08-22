#include "canvasview.h"

CanvasView::CanvasView(QWidget *parent) :
    QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CanvasView::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->x();
    int y = ev->y();
    emit pointClicked (x,y);
}
