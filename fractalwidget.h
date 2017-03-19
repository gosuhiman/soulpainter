#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QWidget>
#include <QGridLayout>

class RenderArea;
class MandelbrotModel;

class FractalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FractalWidget(QWidget* parent = 0, MandelbrotModel* _mandelbrotModel = 0);

signals:

public slots:

protected:

private:
    MandelbrotModel* mandelbrotModel;
    RenderArea* renderArea;
};

#endif // FRACTALWIDGET_H
