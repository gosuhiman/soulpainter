#include "coloringmode.h"
#include "smoothcoloringmode.h"
#include <QColor>

SmoothColoringMode::SmoothColoringMode(FractalOptions* options) : ColoringMode(options)
{
    label = tr("Smooth");
}

QRgb SmoothColoringMode::getColor(int i, Complex z)
{
    float hue = i + 1 - (std::log(std::abs(z)) / std::log(2));
    while(hue > 360) hue -= 360;
    while(hue < 0) hue += 360;
    return (QColor::fromHsv(hue, 0.8 * 255, 255)).rgb();
}
