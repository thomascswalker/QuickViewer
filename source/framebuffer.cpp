#include "framebuffer.h"
#include "rendertask.h"

Framebuffer::Framebuffer(QWidget* parent)
    : QOpenGLWidget(parent)
{
    rendertask = new RenderTask();
}

void Framebuffer::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    rendertask->paint(&painter, event);
    painter.end();
}