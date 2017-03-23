#include "renderarea.h"
#include "mandelbrotmodel.h"

RenderArea::RenderArea(QWidget* parent, MandelbrotModel* _mandelbrotModel) : QWidget(parent), _mandelbrotModel(_mandelbrotModel)
{
    _mandelbrotModel->options->width = width();
    _mandelbrotModel->options->height = height();
    _mandelbrotModel->onResize();
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
    //_pixels = uchar[_mandelbrotModel->options->width * _mandelbrotModel->options->height];
    QImage image = QImage((uchar*)_mandelbrotModel->pixels, width(), height(), QImage::Format_ARGB32);
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void RenderArea::resizeEvent(QResizeEvent *)
{
    _mandelbrotModel->options->width = width();
    _mandelbrotModel->options->height = height();
    _mandelbrotModel->onResize();
    this->repaint();
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
    QPoint clickedPoint = event->pos();
    _mandelbrotModel->zoomIn(clickedPoint.x(), clickedPoint.y());
    this->repaint();
}
