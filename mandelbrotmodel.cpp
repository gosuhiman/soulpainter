#include "mandelbrotmodel.h"

MandelbrotModel::MandelbrotModel()
{
    options = new FractalOptions();
    options->maxIterations = 100;
    options->width = 800;
    options->height = 600;
    options->zoomAmmount = 3;

    palette = new QRgb[options->maxIterations];
    pixels = new QRgb[options->width * options->height];

    buildPalette();

    defaultViewport = ComplexPlane<double>(-2.4, -1.2, 0.9, 1.2);
    viewport = defaultViewport;
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
    Complex c, z;
    int i;

    for (int px = 0; px < options->width; px++)
    {
        for (int py = 0; py < options->height; py++)
        {
            c = transformToComplexPlane(px, py);
            z = Complex(0);
            i = 0;

            while(abs(z) < 2 && i < options->maxIterations)
            {
                z = z*z + c;
                i++;
            }

            pixels[px + py * options->width] = palette[i];
        }
    }
}

void MandelbrotModel::zoomIn(float x, float y)
{
    Complex zoomPoint = transformToComplexPlane(x, y);
    viewport.zoomTo(zoomPoint.real(), zoomPoint.imag(), options->zoomAmmount);
    generate();
}

void MandelbrotModel::onResize()
{
    delete[] pixels;
    pixels = new QRgb[options->width * options->height];

    generate();
}

Complex MandelbrotModel::transformToComplexPlane(int x, int y)
{
    Complex c((double)x / (double)options->width * viewport.width() + viewport.minX,
              (double)y / (double)options->height * viewport.height() + viewport.minY);
    return c;
}
