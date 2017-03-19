#include "mandelbrotmodel.h"

MandelbrotModel::MandelbrotModel()
{
    options = new FractalOptions();
    options->maxIterations = 1000;
    options->width = 400;
    options->height = 400;

    palette = new QRgb[options->maxIterations];
    pixels = new QRgb[options->width * options->height];

    buildPalette();

    plane.minX = -2.5f;
    plane.maxX = 1.f;
    plane.minY = -1.f;
    plane.maxY = 1.f;
}

void MandelbrotModel::buildPalette()
{
    int r;

    for (int i = 0; i < options->maxIterations; i++)
    {
        r = i * (100.f / options->maxIterations) + 155;
        palette[i] = qRgb(r, 20, 20);
    }
}


void MandelbrotModel::generate()
{
    float x0, y0, x, y, sX, sY, xTmp;
    int i;

    sX = (plane.maxX - plane.minX) / options->width;
    sY = (plane.maxY - plane.minY) / options->height;

    for (int px = 0; px < options->width; px++)
    {
        for (int py = 0; py < options->height; py++)
        {
            x0 = px * sX + plane.minX;
            y0 = py * sY + plane.minY;
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

            pixels[px + py * options->height] = palette[i];
        }
    }
}

void MandelbrotModel::onResize()
{
    delete[] pixels;
    pixels = new QRgb[options->width * options->height];

    generate();
}
