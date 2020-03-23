#ifndef	RENDERTASK_H
#define RENDERTASK_H

#include <QPainter>
#include <QPaintEvent>
#include <QBrush>

class RenderTask
{

public:
    RenderTask();
    ~RenderTask();
    void RenderFrame(QPainter* painter, QPaintEvent *event, QImage image, QPoint pos, qreal scale);

private:
    QBrush mBackground;
};

#endif