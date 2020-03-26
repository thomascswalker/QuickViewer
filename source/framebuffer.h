#ifndef	FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QDebug>
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_0>

class RenderTask;

class Framebuffer : public QOpenGLWidget
{
    Q_OBJECT

public:
    Framebuffer(QWidget* parent);
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event);
    void SetImage(QImage image);

public slots:
    void setXPosition(int pos);
    void setYPosition(int pos);
    void setScale(qreal scale);
    void setExposure(float exposure);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    QOpenGLContext* mContext;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    RenderTask* rendertask;
    QOpenGLTexture* mColorbuffer;
    QOpenGLFramebufferObject* FBO;
    QImage* mImage;

    int xPos;
    int yPos;
    QPoint lastPos;
    qreal mScale;

    float mExposure;
};

#endif