#include "rendertask.h"

#include <QImage>
#include <QPixmap>
#include <QColorSpace>
#include <cmath>

RenderTask::RenderTask(int role, QPixmap pixmap, QObject* parent)
    : mRole(role),
    mPixmap(pixmap),
    QObject(parent)

{

}

RenderTask::~RenderTask()
{

}

void RenderTask::doWork()
{
    QImage image(mPixmap.toImage());
    QColorSpace colorspace;

    switch (mRole)
    {
    case 0:
        colorspace = QColorSpace(QColorSpace::SRgbLinear);
        image.convertToColorSpace(colorspace);
        break;
    case 1:
        colorspace = QColorSpace(QColorSpace::SRgb);
        image.convertToColorSpace(colorspace);
        break;
    }

    const QPixmap newPixmap = QPixmap::fromImage(image);
    emit workFinished(newPixmap);
}