#include "coloringmode.h"
#include "basiccoloringmode.h"

BasicColoringMode::BasicColoringMode(FractalOptions* options) : ColoringMode(options)
{
    label = tr("Basic");

    _palette = new QRgb[options->width * options->height];
    buildPalette();
}

void BasicColoringMode::buildPalette()
{
    int r, g, b;

    for (int i = 0; i < _options->maxIterations; i++)
    {
        r = i * 100.f / _options->maxIterations;
        g = i * 255.f / _options->maxIterations;
        b = i * 50.f / _options->maxIterations;
        _palette[i] = qRgb(r, g, b);
    }
}

QRgb BasicColoringMode::getColor(int i, Complex)
{
    return _palette[i];
}
