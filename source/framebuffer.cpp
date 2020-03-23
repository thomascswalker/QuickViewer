#include "framebuffer.h"
#include "rendertask.h"

Framebuffer::Framebuffer(QWidget* parent)
    : QOpenGLWidget(parent)
{
    rendertask = new RenderTask();

    xPos = 0;
    yPos = 0;
    mScale = 1.0;
}

void Framebuffer::initializeGL()
{
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
}

void Framebuffer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    float aspect = (float)w / (float)h;
    glOrtho(-aspect, aspect, -1, 1, -1, 1);
}

void Framebuffer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(xPos, yPos, 1.0f);
    glScalef(mScale, mScale, 1.0f);
}

void Framebuffer::setXPosition(int pos)
{
    if (xPos != pos)
    {
        xPos = pos;
        update();
    }
}

void Framebuffer::setYPosition(int pos)
{
    if (yPos != pos)
    {
        yPos = pos;
        update();
    }
}

void Framebuffer::setScale(qreal scale)
{
    if (mScale != scale)
    {
        mScale *= scale;
        update();
    }
}

void Framebuffer::mousePressEvent(QMouseEvent* event)
{
    lastPos = event->pos();
}

void Framebuffer::mouseMoveEvent(QMouseEvent* event)
{
    int deltaX = event->x() - lastPos.x();
    int deltaY = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXPosition(xPos + (1.5 * deltaX) / mScale);
        setYPosition(yPos + (1.5 * deltaY) / mScale);
    }

    lastPos = event->pos();
}

void Framebuffer::wheelEvent(QWheelEvent* event)
{
    qDebug() << event->delta();
    if (event->delta() >= 0)
    {
        setScale(qreal(1.15));
    }
    else
    {
        setScale(qreal(.85));
    }
    
}

void Framebuffer::paintEvent(QPaintEvent* event)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QPainter painter(this);
    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing);
    rendertask->RenderFrame(&painter, event, mImage, QPoint(xPos, yPos), mScale);

    painter.end();
}

void Framebuffer::SetImage(QImage image)
{
    mImage = image;
}