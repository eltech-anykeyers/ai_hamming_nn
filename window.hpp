#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>

#include <grid_drawer/marked_drawer.hpp>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = Q_NULLPTR);
    ~Window();

private:
    void setupUi();

    QWidget* mainWidget;
    QHBoxLayout* mainLayout;
    QVBoxLayout* leftLayout;
    QLabel* leftLayoutLabel;
    MarkedDrawer* drawer;
    QHBoxLayout* leftButtonsLayout;
    QPushButton* sampleButton;
    QPushButton* recognizeButton;
    QVBoxLayout* rightLayout;
    QLabel* rightLayoutLabel;
    QGridLayout* rightSamplesLayout;
    QPushButton* clearButton;

    QVector<MarkedDrawer*>* samples;

    void redrawSamples();
};

#endif // WINDOW_HPP
