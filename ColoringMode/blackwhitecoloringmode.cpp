#include "coloringmode.h"
#include "blackwhitecoloringmode.h"

BlackWhiteColoringMode::BlackWhiteColoringMode(FractalOptions* options) : ColoringMode(options)
{
    label = tr("Black & White");
}

QRgb BlackWhiteColoringMode::getColor(int i)
{
    QRgb color;

    if (i == _options->maxIterations)
    {
        color = qRgb(255, 255, 255);
    }
    else
    {
        color = qRgb(0, 0, 0);
    }

    return color;
}
