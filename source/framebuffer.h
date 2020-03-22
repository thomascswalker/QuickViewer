#ifndef	FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QOpenGLWidget>

class RenderTask;

class Framebuffer : public QOpenGLWidget
{
    Q_OBJECT

public:
    Framebuffer(QWidget* parent);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    RenderTask* rendertask;
};

#endif