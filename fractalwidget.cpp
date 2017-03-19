#include "fractalwidget.h"

FractalWidget::FractalWidget(QWidget *parent) : QWidget(parent)
{
    options.maxIterations = 1000;

    pixels = new QRgb[width()*height()];
    palette = new QRgb[options.maxIterations];

    buildPalette();

    plane.minX = -2.5f;
    plane.maxX = 1.f;
    plane.minY = -1.f;
    plane.maxY = 1.f;
}

void FractalWidget::setOptions(FractalOptions newOptions)
{
    options = newOptions;
    palette = new QRgb[options.maxIterations];

    buildPalette();
}

void FractalWidget::paintEvent(QPaintEvent*)
{
    if (image != NULL)
    {
        QPainter painter(this);
        painter.drawImage(0, 0, *image);
    }
}

void FractalWidget::resizeEvent(QResizeEvent*)
{
    pixels = new QRgb[width()*height()];
    draw();
}

void FractalWidget::draw()
{
    float x0, y0, x, y, sX, sY, xTmp;
    int i;

    sX = (plane.maxX - plane.minX) / width();
    sY = (plane.maxY - plane.minY) / height();

    for (int px = 0; px < width(); px++)
    {
        for (int py = 0; py < height(); py++)
        {
            x0 = px * sX + plane.minX;
            y0 = py * sY + plane.minY;
            x = 0;
            y = 0;
            i = 0;

            while(x*x + y*y < 2*2 && i < options.maxIterations)
            {
                xTmp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xTmp;
                i++;
            }

            pixels[px + py * height()] = palette[i];
        }
    }

    image = new QImage((uchar*)pixels, width(), height(), QImage::Format_ARGB32);
    this->repaint();
}

void FractalWidget::buildPalette()
{
    int r;

    for (int i = 0; i < options.maxIterations; i++)
    {
        r = i * (100.f / options.maxIterations) + 155;
        palette[i] = qRgb(r, 20, 20);
    }
}
