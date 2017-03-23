#ifndef COLORINGMODE_H
#define COLORINGMODE_H

#include <QObject>
#include <QRgb>
#include "fractaloptions.h"

class ColoringMode : public QObject
{
    Q_OBJECT
public:
    ColoringMode(FractalOptions* options);
    QString label;
    virtual QRgb getColor(int i) = 0;

protected:
    FractalOptions* _options;
};

#endif // COLORINGMODE_H
