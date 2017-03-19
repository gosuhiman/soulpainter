#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDebug>

struct FractalOptions
{
    int maxIterations;
};

struct ComplexPlane
{
    float minX;
    float maxX;
    float minY;
    float maxY;
};

struct Step
{
    float x;
    float y;
};

class FractalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FractalWidget(QWidget *parent = 0);
    void setOptions(FractalOptions newOptions);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void draw();

signals:

public slots:

private:
    FractalOptions options;
    QRgb* pixels;
    QImage* image;
    ComplexPlane plane;
    QRgb* palette;

    void buildPalette();
};

#endif // FRACTALWIDGET_H
