#ifndef SMOOTHCOLORINGMODE_H
#define SMOOTHCOLORINGMODE_H

#include "coloringmode.h"

class SmoothColoringMode : public ColoringMode
{
public:
    SmoothColoringMode(FractalOptions* options);
    QRgb getColor(int i, Complex z);
};

#endif // SMOOTHCOLORINGMODE_H
