#ifndef	FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QDebug>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QWheelEvent>

class Framebuffer : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Framebuffer(QWidget* parent = Q_NULLPTR);
    ~Framebuffer();

    virtual void wheelEvent(QWheelEvent* event);

private:
    QGraphicsScene m_scene;
    QGraphicsPixmapItem m_item;
};

#endif