#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class CanvasView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CanvasView(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);

signals:
    void pointClicked (int x, int y);
public slots:

};

#endif // CANVASVIEW_H
