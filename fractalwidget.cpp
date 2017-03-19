#include "fractalwidget.h"
#include "renderarea.h"

FractalWidget::FractalWidget(QWidget* parent, MandelbrotModel* _mandelbrotModel) : QWidget(parent)
{
    mandelbrotModel = _mandelbrotModel;
    renderArea = new RenderArea(NULL, mandelbrotModel);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    setLayout(mainLayout);
}
