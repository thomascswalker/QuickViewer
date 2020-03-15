#ifndef	RENDERTASK_H
#define RENDERTASK_H

#include <QThread>
#include <QPixmap>

class RenderTask : public QObject
{
    Q_OBJECT

public:
    RenderTask(int role, QPixmap pixmap, QObject* parent = nullptr);
    ~RenderTask();



public slots:
    void doWork();

signals:
    void workFinished(const QPixmap& pixmap);

private:
    int mRole = 0;
    QPixmap mPixmap;
};

#endif 