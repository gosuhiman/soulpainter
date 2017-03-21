#include "mandelbrotmodel.h"
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;

MandelbrotModel::MandelbrotModel()
{
    options = new FractalOptions();
    options->maxIterations = 100;
    options->width = 800;
    options->height = 600;
    options->zoomAmmount = 3;
    options->threadCount = 4;

    palette = new QRgb[options->maxIterations];
    pixels = new QRgb[options->width * options->height];

    buildPalette();

    defaultViewport = ComplexPlane<double>(-2.4, -1.2, 0.9, 1.2);
    viewport = defaultViewport;
}

void MandelbrotModel::buildPalette()
{
    int r;

    for (int i = 0; i < options->maxIterations; i++)
    {
        r =  i * 205.f / options->maxIterations + 50;
        palette[i] = qRgb(r, 20, 20);
    }
}

void MandelbrotModel::generate()
{
    auto start = std::chrono::steady_clock::now();

    int sizeX = options->width / options->threadCount;
    int fromX, toX;

    std::vector<std::thread> threads;

    for (int t = 0; t < options->threadCount; t++)
    {
        fromX = t * sizeX;
        toX = fromX + sizeX;
        std::thread thread(&MandelbrotModel::generatePart, this, fromX, toX);
        threads.push_back(std::move(thread));
    }

    for (int t = 0; t < options->threadCount; t++)
    {
        threads[t].join();
    }

    auto end = std::chrono::steady_clock::now();
    qDebug() << "time =" << std::chrono::duration<double, std::milli> (end - start).count() << "milliseconds";
}

void MandelbrotModel::generatePart(int fromX, int toX)
{
    for (int px = fromX; px < toX; px++)
    {
        for (int py = 0; py < options->height; py++)
        {
            Complex c = transformToComplexPlane(px, py);
            Complex z = Complex(0);
            int i = getIterationCount(c, z);
            mtx.lock();
            pixels[px + py * options->width] = palette[i];
            mtx.unlock();
        }
    }
    qDebug() << "generatePart finish" << fromX << toX;
}

int MandelbrotModel::getIterationCount(Complex c, Complex z)
{
    int i = 0;

    while(abs(z) < 2 && i < options->maxIterations)
    {
        z = z*z + c;
        i++;
    }

    return i;
}

void MandelbrotModel::zoomIn(float x, float y)
{
    Complex zoomPoint = transformToComplexPlane(x, y);
    viewport.zoomTo(zoomPoint.real(), zoomPoint.imag(), options->zoomAmmount);
    generate();
}

void MandelbrotModel::onResize()
{
    delete[] pixels;
    pixels = new QRgb[options->width * options->height];

    generate();
}

Complex MandelbrotModel::transformToComplexPlane(int x, int y)
{
    Complex c((double)x / (double)options->width * viewport.width() + viewport.minX,
              (double)y / (double)options->height * viewport.height() + viewport.minY);
    return c;
}
