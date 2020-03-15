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
    QThread* thread = new QThread();
    RenderTask* task = new RenderTask(role, *mPixmap);
    
    // move the task object to the thread BEFORE connecting any signal/slots
    task->moveToThread(thread);
    (void)connect(thread, &QThread::started, task, &RenderTask::SetColorspace);
    (void)connect(task, &RenderTask::workFinished, thread, &QThread::quit);

    // Connect the work finished signal to the UpdatePixmap function
    // in order to actually update the scene pixmap when it's complete
    // Delete thread when tasks are finished
    (void)connect(task, &RenderTask::workFinished, this, &Framebuffer::UpdatePixmap);
    (void)connect(thread, &QThread::finished, thread, &RenderTask::deleteLater);

    // At this point we can start the thread
    thread->start();
}

/*
    Returns void.

    Sets the exposure of the currently-viewed image.
*/
void Framebuffer::SetExposure(double value)
{
    QThread* thread = new QThread();
    RenderTask* task = new RenderTask(value, *kPixmap);

    // move the task object to the thread BEFORE connecting any signal/slots
    task->moveToThread(thread);
    (void)connect(thread, &QThread::started, task, &RenderTask::SetExposure);
    (void)connect(task, &RenderTask::workFinished, thread, &QThread::quit);

    // Connect the work finished signal to the UpdatePixmap function
    // in order to actually update the scene pixmap when it's complete
    // Delete thread when tasks are finished
    (void)connect(task, &RenderTask::workUpdated, this, &Framebuffer::UpdatePixmap);
    (void)connect(task, &RenderTask::workFinished, this, &Framebuffer::UpdatePixmap);
    (void)connect(thread, &QThread::finished, thread, &RenderTask::deleteLater);

    // At this point we can start the thread
    thread->start();
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