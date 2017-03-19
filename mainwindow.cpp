#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fractalwidget.h"
#include "mandelbrotmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mandelbrotModel = new MandelbrotModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    fractalWidget = new FractalWidget(NULL, mandelbrotModel);
    fractalWidget->show();
}
