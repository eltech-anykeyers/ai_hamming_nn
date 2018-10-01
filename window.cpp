#include <window.hpp>

Window::Window(QWidget* parent)
    : QMainWindow(parent)
{
    samples = new QVector<MarkedDrawer*>();

    setupUi();
}

Window::~Window()
{

}

void Window::setupUi()
{
    mainWidget = new QWidget(this);
    this->setCentralWidget(mainWidget);

    mainLayout = new QHBoxLayout(mainWidget);

    leftLayout = new QVBoxLayout(mainWidget);
    mainLayout->addLayout(leftLayout);

    leftLayoutLabel = new QLabel(mainWidget);
    leftLayoutLabel->setText(QString::fromWCharArray(L"Input image"));
    leftLayout->addWidget(leftLayoutLabel);
    leftLayout->setAlignment(leftLayoutLabel, Qt::AlignTop | Qt::AlignHCenter);

    drawer = new MarkedDrawer(QSize(3, 3), mainWidget);
    leftLayout->addWidget(drawer);
    leftLayout->setAlignment(drawer, Qt::AlignVCenter | Qt::AlignHCenter);

    leftButtonsLayout = new QHBoxLayout(mainWidget);
    leftLayout->addLayout(leftButtonsLayout);
    leftLayout->setAlignment(leftButtonsLayout, Qt::AlignBottom | Qt::AlignHCenter);

    sampleButton = new QPushButton(mainWidget);
    sampleButton->setText(QString::fromWCharArray(L"Sample"));
    leftButtonsLayout->addWidget(sampleButton);

    recognizeButton = new QPushButton(mainWidget);
    recognizeButton->setText(QString::fromWCharArray(L"Recognize"));
    leftButtonsLayout->addWidget(recognizeButton);

    rightLayout = new QVBoxLayout(mainWidget);
    mainLayout->addLayout(rightLayout);

    rightLayoutLabel = new QLabel(mainWidget);
    rightLayoutLabel->setText(QString::fromWCharArray(L"Samples"));
    rightLayout->addWidget(rightLayoutLabel);
    rightLayout->setAlignment(rightLayoutLabel, Qt::AlignTop | Qt::AlignHCenter);

    rightSamplesLayout = new QGridLayout(mainWidget);
    rightLayout->addLayout(rightSamplesLayout);
    rightLayout->setAlignment(rightSamplesLayout, Qt::AlignVCenter | Qt::AlignHCenter);

    clearButton = new QPushButton(mainWidget);
    clearButton->setText(QString::fromWCharArray(L"Clear"));
    rightLayout->addWidget(clearButton);
    rightLayout->setAlignment(clearButton, Qt::AlignBottom | Qt::AlignHCenter);
}

void Window::redrawSamples()
{
    for (const auto widget : rightSamplesLayout->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly))
    {
        delete widget;
    }

    qint8 i = 0, j = 0;
    for (const auto& drawer : *samples)
    {
        rightSamplesLayout->addWidget(drawer, i, j);

        if(++j > 2)
        {
            ++i;
            j = 0;
        }
    }
}
