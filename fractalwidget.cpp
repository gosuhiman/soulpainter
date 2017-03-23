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

    for (const ColoringMode* coloringMode : mandelbrotModel->coloringModes)
    {
        ui->coloringModeComboBox->addItem(coloringMode->label);
    }

    connect(mandelbrotModel, SIGNAL(progressChanged(float)), this, SLOT(setProgress(float)));
    connect(ui->coloringModeComboBox, SIGNAL(activated(int)), this, SLOT(setColoringMode(int)));
}

FractalWidget::~FractalWidget()
{
    delete ui;
}

void FractalWidget::setColoringMode(int colorModeIndex)
{
    mandelbrotModel->setColoringMode(mandelbrotModel->coloringModes[colorModeIndex]);
    mandelbrotModel->generate();
    renderArea->repaint();
}

void FractalWidget::setProgress(float progress)
{
    ui->generateProgressBar->setValue(progress * 100);
}
