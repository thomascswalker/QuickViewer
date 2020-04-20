#include "framebuffer.h"
#include "rendertask.h"
#include <QtGui>

Framebuffer::Framebuffer(QWidget* parent)
    : QOpenGLWidget(parent)
{
    rendertask = new RenderTask();

    xPos = 0;
    xOffset = 0;
    yPos = 0;
    yOffset = 0;
    mScale = 1.0;
}

void Framebuffer::initializeGL()
{
    QSurfaceFormat format;
    format.setVersion(4, 5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);

    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)this->width() / (float)this->height();
    glOrtho(-aspect, aspect, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0f);
    glScalef(mScale, mScale, 1.0f);

    glBegin(GL_QUADS);
        glVertex3f(-1, -1, 0);
        glVertex3f(-1, 1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(1, -1, 0);
    glEnd();
}

void Framebuffer::setXPosition(int pos)
{
    qDebug() << pos;
    if (xPos != pos)
    {
        xPos = pos;
        update();
    }
}

void Framebuffer::setYPosition(int pos)
{
    qDebug() << pos;
    if (yPos != pos)
    {
        yPos = pos;
        update();
    }
}

void Framebuffer::setScale(float scale)
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
    if (event->buttons() & Qt::MiddleButton) {
        int xDelta = event->x() - lastPos.x();
        int yDelta = event->y() - lastPos.y();

        qDebug() << "Delta:" << xDelta << yDelta;

        //xOffset = (float)xDelta / (float)this->width();
        //yOffset = (float)yDelta / (float)this->height();
        //xOffset = (float)xDelta / 100.0f;
        //yOffset = (float)yDelta / -100.0f;
        xOffset = (float)event->x() / (float)this->width();
        yOffset = (float)event->y() / -(float)this->height();

        qDebug() << "Offset:" << xOffset << yOffset;

        lastPos = event->pos();
        update();
    }
}

void Framebuffer::wheelEvent(QWheelEvent* event)
{
    if (event->delta() >= 0)
    {
        setScale(float(1.15));
    }
    else
    {
        setScale(float(.85));
    }
    
}

/*
void Framebuffer::paintEvent(QPaintEvent* event)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QPainter painter(this);

    if (!painter.isActive())
    {
        painter.begin(this);
    }

    painter.setRenderHint(QPainter::Antialiasing);
    rendertask->RenderFrame(&painter, event, mImage, QPoint(xPos, yPos), mScale);

    if (painter.isActive())
    {
        painter.end();
    }
}
*/

void Framebuffer::SetImage(QImage image)
{
    mImage = image;
    update();
}