#include "fractalwidget.h"
#include "ui_fractalwidget.h"
#include "renderarea.h"
#include "mandelbrotmodel.h"

FractalWidget::FractalWidget(QWidget* parent, MandelbrotModel* _mandelbrotModel) : QWidget(parent), ui(new Ui::FractalWidget)
{
    mandelbrotModel = _mandelbrotModel;
    renderArea = new RenderArea(NULL, mandelbrotModel);
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, renderArea);

    QObject::connect(mandelbrotModel, SIGNAL(progressChanged(float)), this, SLOT(setProgress(float)));
}

FractalWidget::~FractalWidget()
{
    delete ui;
}

void FractalWidget::setProgress(float progress)
{
    ui->progressBar->setValue(progress * 100);
}
