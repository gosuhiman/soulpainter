#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

class MandelbrotModel;

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0, MandelbrotModel* _mandelbrotModel = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    MandelbrotModel* _mandelbrotModel;
    uchar* _pixels;
};

#endif // RENDERAREA_H
