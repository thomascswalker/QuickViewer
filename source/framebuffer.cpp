#include "framebuffer.h"

Framebuffer::Framebuffer(QWidget* parent) :
    QGraphicsView(parent)
{
    mCurrentZoom = 1.0;
    mColorspace = Linear;
}
   
Framebuffer::~Framebuffer()
{

}

/*
    Returns void.

    Sets the colorspace of the currently-viewed image. This loads
    the current image, converts to the chosen colorspace, then
    sets the current scene image to the converted image.
*/
void Framebuffer::SetColorspace(int role)
{
    mColorspace = Qt::UserRole + role;

    switch (mColorspace)
    {
        case Linear:
            qDebug() << "Linear";
            break;
        case sRGB:
            qDebug() << "sRGB";
            break;
    }
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