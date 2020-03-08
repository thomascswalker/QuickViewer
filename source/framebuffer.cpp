#include "framebuffer.h"

Framebuffer::Framebuffer(QWidget* parent) :
    QGraphicsView(parent)
{
    mCurrentZoom = 1.0;
}
   
Framebuffer::~Framebuffer()
{

}

/*
    Returns void.

    The custom wheel event to allow for middle-mouse scrolling.
    This also affects the zoom percent UI item.
*/
void Framebuffer::wheelEvent(QWheelEvent* event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if (event->delta() > 0)
    {
        // Zoom in
        scale(scaleFactor, scaleFactor);
        mCurrentZoom *= scaleFactor;
    }
    else
    {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        mCurrentZoom /= scaleFactor;
    }

    // Update GUI items
    emit middleMouseScroll(mCurrentZoom);
    QGraphicsView::wheelEvent(event);
}