#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

class FractalWidget;
class MandelbrotModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();

private:
    Ui::MainWindow* ui;
    FractalWidget* fractalWidget;
    MandelbrotModel* mandelbrotModel;
};

#endif // MAINWINDOW_H
