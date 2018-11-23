#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>

#include <hamming.hpp>
#include <grid_drawer/marked_drawer.hpp>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget* parent = Q_NULLPTR);
    ~Window();

private:
    static const QSize imageSize;

    void setupUi();
    void setupObj();

    QWidget* mainWidget;
    QHBoxLayout* mainLayout;
    QGridLayout* leftLayout;
    QLabel* leftLayoutLabel;
    MarkedDrawer* drawer;
    QHBoxLayout* leftButtonsLayout;
    QPushButton* sampleButton;
    QPushButton* recognizeButton;
    QLabel* resultLabel;
    QVBoxLayout* rightLayout;
    QLabel* rightLayoutLabel;
    QGridLayout* rightSamplesLayout;
    QPushButton* clearButton;

    QVector<MarkedDrawer*>* samples;

    Hamming* ai;

    void redrawSamples();
};

#endif // WINDOW_HPP
