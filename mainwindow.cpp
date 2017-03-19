#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fractalwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    if (fractalWidget == NULL)
    {
        fractalWidget = new FractalWidget();

        FractalOptions options = FractalOptions();
        options.maxIterations = 1000;
        fractalWidget->setOptions(options);

        fractalWidget->draw();
        fractalWidget->show();
    }
    else
    {
        FractalOptions options = FractalOptions();
        options.maxIterations = 1000;
        fractalWidget->setOptions(options);

        fractalWidget->draw();
        fractalWidget->show();
    }
}
