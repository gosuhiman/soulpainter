#include "renderarea.h"
#include "mandelbrotmodel.h"

RenderArea::RenderArea(QWidget* parent, MandelbrotModel* _mandelbrotModel) : QWidget(parent)
{
    mandelbrotModel = _mandelbrotModel;

    mandelbrotModel->options->width = width();
    mandelbrotModel->options->height = height();
    mandelbrotModel->onResize();
}

QSize RenderArea::sizeHint() const
{
    return QSize(800, 600);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QImage image = QImage((uchar*)mandelbrotModel->pixels, width(), height(), QImage::Format_ARGB32);
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void RenderArea::resizeEvent(QResizeEvent *)
{
    mandelbrotModel->options->width = width();
    mandelbrotModel->options->height = height();
    mandelbrotModel->onResize();
}
