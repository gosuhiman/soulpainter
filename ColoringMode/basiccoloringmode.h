#ifndef BASICCOLORINGMODE_H
#define BASICCOLORINGMODE_H

#include "coloringmode.h"

class BasicColoringMode : public ColoringMode
{
public:
    BasicColoringMode(FractalOptions* options);
    void buildPalette();
    QRgb getColor(int i, Complex z);

private:
    QRgb* _palette;
};

#endif // BASICCOLORINGMODE_H
