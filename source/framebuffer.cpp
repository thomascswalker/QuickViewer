#include "framebuffer.h"
#include "rendertask.h"
#include <thread>
#include <QThread>

Framebuffer::Framebuffer(QWidget* parent) :
    QGraphicsView(parent)
{
    mCurrentZoom = 1.0;
    mColorspace = Linear;

    mScene = new QGraphicsScene(this);
    mPixmap = new QPixmap("");
    mScene->addPixmap(*mPixmap);
    setScene(mScene);
}
   
Framebuffer::~Framebuffer()
{

}

void Framebuffer::AddPixmap(QPixmap pixmap)
{
    mPixmap = new QPixmap(pixmap);
    kPixmap = mPixmap;
    mScene->clear();
    mScene->addPixmap(pixmap);
    mScene->setSceneRect(mScene->itemsBoundingRect());
}

void Framebuffer::UpdatePixmap(QPixmap pixmap)
{
    mPixmap = new QPixmap(pixmap);
    mScene->clear();
    mScene->addPixmap(pixmap);
    mScene->setSceneRect(mScene->itemsBoundingRect());
}

/*
    Returns void.

    Sets the colorspace of the currently-viewed image. This loads
    the current image, converts to the chosen colorspace, then
    sets the current scene image to the converted image.
*/
void Framebuffer::SetColorspace(int role)
{
    /*
        get image
        start new thread
        update image on new thread
        return image
        update viewport
    */

    QThread* thread = new QThread();
    RenderTask* task = new RenderTask(role, *mPixmap);
    qDebug() << role;
    
    // move the task object to the thread BEFORE connecting any signal/slots
    task->moveToThread(thread);
    connect(thread, &QThread::started, task, &RenderTask::doWork);
    connect(task, &RenderTask::workFinished, thread, &QThread::quit);

    // Connect the work finished signal to the UpdatePixmap function
    // in order to actually update the scene pixmap when it's complete
    // Delete thread when tasks are finished
    connect(task, &RenderTask::workFinished, this, &Framebuffer::UpdatePixmap);
    connect(thread, &QThread::finished, thread, &RenderTask::deleteLater);

    // At this point we can start the thread
    thread->start();
}

/*
    Returns void.

    Sets the exposure of the currently-viewed image.
*/
void Framebuffer::SetExposure(double value)
{
    QImage image(kPixmap->toImage());

    double minp = 1;
    double maxp = 1000;
    double minv = log(.01);
    double maxv = log(10);
    double scale = (maxv - minv) / (maxp - minp);
    double factor = exp(minv + scale * (value - minp));

    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            QPoint pos(x, y);
            QColor pixel(image.pixel(QPoint(x, y)));
            
            int newRed = pixel.red() * factor;
            int newGreen = pixel.green() * factor;
            int newBlue = pixel.blue() * factor;

            if (newRed <= 255)
            {
                pixel.setRed(newRed);
            }
            else
            {
                pixel.setRed(255);
            }

            if (newGreen <= 255)
            {
                pixel.setGreen(newGreen);
            }
            else
            {
                pixel.setGreen(255);
            }

            if (newBlue <= 255)
            {
                pixel.setBlue(newBlue);
            }
            else
            {
                pixel.setBlue(255);
            }

            image.setPixelColor(pos, pixel);
        }
    }

    QPixmap outPixmap = QPixmap::fromImage(image);
    UpdatePixmap(outPixmap);
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