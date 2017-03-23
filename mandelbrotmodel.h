#ifndef MANDELBROTMODEL_H
#define MANDELBROTMODEL_H

#include <QObject>
#include <Qrgb>
#include <QDebug>
#include <complex>
#include <queue>
#include <cmath>
#include "fractaloptions.h"
#include "ColoringMode/coloringmode.h"
#include "ColoringMode/basiccoloringmode.h"
#include "ColoringMode/blackwhitecoloringmode.h"
#include "ColoringMode/grayscalecoloringmode.h"

using Complex = std::complex<double>;

template<typename T> class ComplexPlane
{
public:
    T minX, minY, maxX, maxY;
public:
    ComplexPlane():minX(0), minY(0), maxX(0), maxY(0){}
    ComplexPlane(T minX, T minY, T maxX, T maxY):minX(minX), minY(minY), maxX(maxX), maxY(maxY){}
    T width(){ return maxX - minX; }
    T height(){ return maxY - minY; }

    inline void zoomTo(T x, T y, int zoomAmmount)
    {
        T halfWidth = width() / (zoomAmmount*2);
        T halfHeight = height() / (zoomAmmount*2);
        minX = x - halfWidth;
        maxX = x + halfHeight;
        minY = y - halfWidth;
        maxY = y + halfHeight;
    }
};

class MandelbrotModel : public QObject
{
    Q_OBJECT
public:
    MandelbrotModel();
    void generate();
    void zoomIn(float x, float y);

    void onResize();

    float progress() const { return _progress; }
    void setProgress(float progress);
    ColoringMode* coloringMode() const { return _coloringMode; }
    void setColoringMode(ColoringMode* coloringMode);

    FractalOptions* options;
    std::vector<ColoringMode*> coloringModes;
    ComplexPlane<double> defaultViewport;
    ComplexPlane<double> viewport;
    QRgb* pixels;

signals:
    void progressChanged(float newProgress);

private:
    float _progress;
    ColoringMode* _coloringMode;

    Complex transformToComplexPlane(int x, int y);
    void workOnTasks(std::queue<int>* tasks);
    void generatePixelRow(int py);
    int getIterationCount(Complex c, Complex z);
};

#endif // MANDELBROTMODEL_H
