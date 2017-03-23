#include "coloringmode.h"
#include "grayscalecoloringmode.h"

GrayScaleColoringMode::GrayScaleColoringMode(FractalOptions* options) : ColoringMode(options)
{
    label = tr("Grayscale");

    _palette = new QRgb[options->width * options->height];
    buildPalette();
}

void GrayScaleColoringMode::buildPalette()
{
    int r, g, b;

    for (int i = 0; i < _options->maxIterations; i++)
    {
        r = i * 255.f / _options->maxIterations;
        g = i * 255.f / _options->maxIterations;
        b = i * 255.f / _options->maxIterations;
        _palette[i] = qRgb(r, g, b);
    }
}

QRgb GrayScaleColoringMode::getColor(int i)
{
    return _palette[i];
}
