#include "mandelbrotmodel.h"
#include <cmath>

MandelbrotModel::MandelbrotModel()
{
    options = new FractalOptions();
    options->maxIterations = 1000;
    options->width = 800;
    options->height = 600;

    palette = new QRgb[options->maxIterations];
    pixels = new QRgb[options->width * options->height];

    buildPalette();

    plane.minX = -2.4f;
    plane.maxX = 0.9f;
    plane.minY = -1.2f;
    plane.maxY = 1.2f;

    viewport = plane;
}

void MandelbrotModel::buildPalette()
{
    int r;

    for (int i = 0; i < options->maxIterations; i++)
    {
        r =  i * 205.f / options->maxIterations + 50;
        palette[i] = qRgb(r, 20, 20);
    }
}


void MandelbrotModel::generate()
{
    double x0, y0, x, y, sX, sY, xTmp;
    int i;
    int pointCount = 0;

    sX = (viewport.maxX - viewport.minX) / options->width;
    sY = (viewport.maxY - viewport.minY) / options->height;

    for (int px = 0; px < options->width; px++)
    {
        for (int py = 0; py < options->height; py++)
        {
            x0 = px * sX + viewport.minX;
            y0 = py * sY + viewport.minY;
            x = 0;
            y = 0;
            i = 0;

            while(x*x + y*y < 2*2 && i < options->maxIterations)
            {
                xTmp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xTmp;
                i++;
            }

            pixels[px + py * options->width] = palette[i];
            pointCount++;
        }
    }
}

void MandelbrotModel::zoomIn(float x, float y)
{
    x = x * (viewport.maxX - viewport.minX) / options->width + viewport.minX;
    y = y * (viewport.maxY - viewport.minY) / options->height + viewport.minY;

    float halfNewRangeX = std::abs(viewport.maxX - viewport.minX) / 4;
    float halfNewRangeY = std::abs(viewport.maxY - viewport.minY) / 4;

    viewport.minX = x - halfNewRangeX;
    viewport.maxX = x + halfNewRangeX;
    viewport.minY = y - halfNewRangeY;
    viewport.maxY = y + halfNewRangeY;

    generate();
}

void MandelbrotModel::onResize()
{
    delete[] pixels;
    pixels = new QRgb[options->width * options->height];

    generate();
}
