#include "mandelbrotmodel.h"

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
}

void MandelbrotModel::buildPalette()
{
    int r;

    for (int i = 0; i < options->maxIterations; i++)
    {
        if (i > 15)
        {
            r = 205;
        }
        else
        {
            r = 40;
        }
        palette[i] = qRgb(r, 20, 20);
    }
}


void MandelbrotModel::generate()
{
    float x0, y0, x, y, sX, sY, xTmp;
    int i;
    int pointCount = 0;

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

            pixels[px + py * options->width] = palette[i];
            pointCount++;
        }
    }
}

void MandelbrotModel::onResize()
{
    delete[] pixels;
    pixels = new QRgb[options->width * options->height];

    generate();
}
