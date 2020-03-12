#ifndef	FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QDebug>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QWheelEvent>
#include <QColorSpace>

class Framebuffer : public QGraphicsView
{
    Q_OBJECT

public:
    enum Colorspaces {
        Linear = Qt::UserRole,
        sRGB = Qt::UserRole + 1
    };

    explicit Framebuffer(QWidget* parent = Q_NULLPTR);
    ~Framebuffer();
    void AddPixmap(QPixmap pixmap);
    void SetColorspace(int role);
    void SetExposure(double value);

signals:
    void middleMouseScroll(double zoom);

private:
    QGraphicsScene* mScene;
    QPixmap* mPixmap;
    double mCurrentZoom;
    int mColorspace;

protected:
    void wheelEvent(QWheelEvent* event);
};

#endif