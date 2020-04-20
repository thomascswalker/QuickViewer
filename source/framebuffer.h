#ifndef	FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_0>
#include <QDebug>

class RenderTask;

class Framebuffer : public QOpenGLWidget
{
    Q_OBJECT

public:
    Framebuffer(QWidget* parent);
    //void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event);
    void SetImage(QImage image);

public slots:
    void setXPosition(int pos);
    void setYPosition(int pos);
    void setScale(float scale);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    RenderTask* rendertask;
    QImage mImage;

    int xPos;
    float xOffset;
    int yPos;
    float yOffset;
    QPoint lastPos;
    float mScale;
};

#endif