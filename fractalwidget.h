#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QWidget>
#include <QGridLayout>

class RenderArea;
class MandelbrotModel;

namespace Ui {
class FractalWidget;
}

class FractalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FractalWidget(QWidget* parent = 0, MandelbrotModel* _mandelbrotModel = 0);
    ~FractalWidget();

public slots:
    void setProgress(float progress);
    void setColoringMode(int colorModeIndex);

protected:

private:
    Ui::FractalWidget *ui;
    MandelbrotModel* mandelbrotModel;
    RenderArea* renderArea;
};

#endif // FRACTALWIDGET_H
