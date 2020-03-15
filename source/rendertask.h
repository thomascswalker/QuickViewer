#ifndef	RENDERTASK_H
#define RENDERTASK_H

#include <QThread>
#include <QPixmap>

class RenderTask : public QObject
{
    Q_OBJECT

public:
    RenderTask(int role, QPixmap pixmap, QObject* parent = nullptr);
    RenderTask(double value, QPixmap pixmap, QObject* parent = nullptr);
    ~RenderTask();



public slots:
    void SetColorspace();
    void SetExposure();

signals:
    void workUpdated(const QPixmap& pixmap);
    void workFinished(const QPixmap& pixmap);

private:
    int mRole = 0;
    QPixmap mPixmap;
    double mValue = 0;
};

#endif 