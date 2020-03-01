#include "framebuffer.h"

Framebuffer::Framebuffer(QWidget* parent) :
    QGraphicsView(parent)
{

}
   
Framebuffer::~Framebuffer()
{

}

void Framebuffer::wheelEvent(QWheelEvent* event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;

    if (event->delta() > 0)
    {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    }
    else
    {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}