#include "framebuffer.h"
#include "rendertask.h"
#include <QtGui>

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
    //glMatrixMode(GL_PROJECTION);
    //float aspect = (float)w / (float)h;
    //glOrtho(-aspect, aspect, -1, 1, -1, 1);
}

void Framebuffer::paintGL()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glTranslatef(xPos, yPos, 1.0f);
    //glTranslatef(0.0f, 0.0f, 1.0f);
    //glScalef(mScale, mScale, 1.0f);

    glMatrixMode(GL_COLOR);
    glLoadIdentity();

    glBegin(GL_QUADS);
        glVertex3f(-1, -1, 0);
        glVertex3f(-1, 1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(1, -1, 0);
    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Translation is 0 to 1
    glTranslatef(xOffset, yOffset, 0.0f);

    //QPainter p(this);
    //p.setPen(Qt::red);
    //p.drawLine(rect().topLeft(), rect().bottomRight());
}

void Framebuffer::setXPosition(int pos)
{
    if (xPos != pos)
    {
        xPos = pos;
    }
}

void Framebuffer::setYPosition(int pos)
{
    if (yPos != pos)
    {
        yPos = pos;
    }
}

void Framebuffer::setScale(qreal scale)
{
    if (mScale != scale)
    {
        mScale *= scale;
    }
}

void Framebuffer::mousePressEvent(QMouseEvent* event)
{
    lastPos = event->pos();
}

void Framebuffer::mouseMoveEvent(QMouseEvent* event)
{
    // First we need to normalize the width and height
    // event input into 0 to 1
    if (event->buttons() & Qt::LeftButton) {
        float newX = (float)event->x() / (float)this->width();
        float newY = (float)event->y() / (float)this->height();

        float lastX = lastPos.x() / (float)this->width();
        float lastY = lastPos.y() / (float)this->height();

        float xOffset = newX - lastX;
        float yOffset = newY - lastY;

        qDebug() << xOffset << yOffset;

        lastPos = QPoint(newX, newY);
    }
}

void Framebuffer::wheelEvent(QWheelEvent* event)
{
    if (event->delta() >= 0)
    {
        setScale(qreal(1.15));
    }
    else
    {
        setScale(qreal(.85));
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