#include "coloringmode.h"
#include <QDebug>
#include <QRgb>

ColoringMode::ColoringMode(FractalOptions* options) : _options(options)
{
    label = tr("");
}
