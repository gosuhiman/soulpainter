#include "mandelbrotmodel.h"
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;

MandelbrotModel::MandelbrotModel()
{
    options = new FractalOptions();
    pixels = new QRgb[options->width * options->height];

    coloringModes.push_back(new BasicColoringMode(options));
    coloringModes.push_back(new BlackWhiteColoringMode(options));
    coloringModes.push_back(new GrayScaleColoringMode(options));
    coloringModes.push_back(new SmoothColoringMode(options));
    setColoringMode(coloringModes[0]);

    defaultViewport = ComplexPlane<double>(-2.4, -1.2, 0.9, 1.2);
    viewport = defaultViewport;

    setProgress(0);
}

void MandelbrotModel::setColoringMode(ColoringMode* coloringMode)
{
    if (coloringMode != _coloringMode) {
        _coloringMode = coloringMode;
    }
}

void MandelbrotModel::setProgress(float progress)
{
    if (progress != _progress) {
        _progress = progress;
        emit progressChanged(progress);
    }
}

void MandelbrotModel::generate()
{
    auto start = std::chrono::steady_clock::now();

    setProgress(0);

    std::vector<std::thread> threads;
    std::queue<int> tasks;

    for (int py = 0; py < options->height; py++)
    {
        tasks.push(py);
    }

    for (int t = 0; t < options->threadCount; t++)
    {
        std::thread thread(&MandelbrotModel::workOnTasks, this, &tasks);
        threads.push_back(std::move(thread));
    }

    for (int t = 0; t < options->threadCount; t++)
    {
        threads[t].join();
    }

    setProgress(1);

    auto end = std::chrono::steady_clock::now();
    qDebug() << "time =" << std::chrono::duration<double, std::milli> (end - start).count() << "milliseconds";
}

void MandelbrotModel::workOnTasks(std::queue<int>* tasks)
{
    while (tasks->size() > 0)
    {
        mtx.lock();
        int py = tasks->front();
        tasks->pop();
        setProgress((float)(options->height - tasks->size()) / options->height);
        mtx.unlock();
        generatePixelRow(py);
    }
}

void MandelbrotModel::generatePixelRow(int py)
{
    for (int px = 0; px < options->width; px++)
    {
        Complex c = transformToComplexPlane(px, py);
        Complex z = Complex(0);
        int i = 0;

        while(std::abs(z) < 2 && i < options->maxIterations)
        {
            z = z*z + c;
            i++;
        }

        pixels[px + py * options->width] = _coloringMode->getColor(i, z);
    }
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
