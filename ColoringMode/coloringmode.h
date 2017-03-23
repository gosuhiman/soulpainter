#ifndef COLORINGMODE_H
#define COLORINGMODE_H

#include <QObject>
#include <QRgb>
#include "fractaloptions.h"
#include <complex>

using Complex = std::complex<double>;

class ColoringMode : public QObject
{
    Q_OBJECT
public:
    ColoringMode(FractalOptions* options);
    QString label;
    virtual QRgb getColor(int i, Complex z) = 0;

protected:
    FractalOptions* _options;
};

#endif // COLORINGMODE_H
