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

RenderTask::RenderTask(double value, QPixmap pixmap, QObject* parent)
    : mValue(value),
    mPixmap(pixmap),
    QObject(parent)
{

}

RenderTask::~RenderTask()
{

}

void RenderTask::SetColorspace()
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

    const QPixmap outPixmap = QPixmap::fromImage(image);
    emit workFinished(outPixmap);
}

void RenderTask::SetExposure()
{
    QImage image(mPixmap.toImage());

    double minp = 1;
    double maxp = 1000;
    double minv = log(.01);
    double maxv = log(10);
    double scale = (maxv - minv) / (maxp - minp);
    double factor = exp(minv + scale * (mValue - minp));
    double startValue = mValue;

    for (int y = 0; y < image.height(); y++)
    {
        //////
        // We need to find the current value of the Exposure slider in the UI
        // How do we get it? :(
        //////
        if (mValue != startValue)
        {
            break;
        }

        for (int x = 0; x < image.width(); x++)
        {
            QPoint pos(x, y);
            QColor pixel(image.pixel(QPoint(x, y)));

            int newRed = pixel.red() * factor;
            int newGreen = pixel.green() * factor;
            int newBlue = pixel.blue() * factor;

            if (newRed <= 255)
            {
                pixel.setRed(newRed);
            }
            else
            {
                pixel.setRed(255);
            }

            if (newGreen <= 255)
            {
                pixel.setGreen(newGreen);
            }
            else
            {
                pixel.setGreen(255);
            }

            if (newBlue <= 255)
            {
                pixel.setBlue(newBlue);
            }
            else
            {
                pixel.setBlue(255);
            }

            image.setPixelColor(pos, pixel);
        }

        QPixmap outPixmap = QPixmap::fromImage(image);
        emit workUpdated(outPixmap);
    }

    QPixmap outPixmap = QPixmap::fromImage(image);
    emit workFinished(outPixmap);
}