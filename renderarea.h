#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDebug>

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
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    MandelbrotModel* mandelbrotModel;
};

#endif // RENDERAREA_H
