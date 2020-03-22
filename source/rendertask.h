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
    void paint(QPainter* painter, QPaintEvent* event);

private:
    QBrush mBackground;
};

#endif