#ifndef BLACKWHITECOLORINGMODE_H
#define BLACKWHITECOLORINGMODE_H

#include "coloringmode.h"

class BlackWhiteColoringMode : public ColoringMode
{
public:
    BlackWhiteColoringMode(FractalOptions* options);
    QRgb getColor(int i, Complex z);
};

#endif // BLACKWHITECOLORINGMODE_H
