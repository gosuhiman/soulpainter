#ifndef MANDELBROTMODEL_H
#define MANDELBROTMODEL_H

#include <Qrgb>
#include <QDebug>

struct FractalOptions
{
    int maxIterations;
    int width;
    int height;
};

struct ComplexPlane
{
    float minX;
    float maxX;
    float minY;
    float maxY;
};

class MandelbrotModel
{
public:
    MandelbrotModel();
    void buildPalette();
    void generate();

    void onResize();

    FractalOptions* options;
    ComplexPlane plane;
    QRgb* palette;
    QRgb* pixels;
};

#endif // MANDELBROTMODEL_H
