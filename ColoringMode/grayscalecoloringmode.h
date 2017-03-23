#ifndef GRAYSCALECOLORINGMODE_H
#define GRAYSCALECOLORINGMODE_H

#include "coloringmode.h"

class GrayScaleColoringMode : public ColoringMode
{
public:
    GrayScaleColoringMode(FractalOptions* options);
    void buildPalette();
    QRgb getColor(int i);

private:
    QRgb* _palette;
};

#endif // GRAYSCALECOLORINGMODE_H
