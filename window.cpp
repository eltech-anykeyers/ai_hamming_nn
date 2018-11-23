#include <QDebug>

#include <window.hpp>

const QSize Window::imageSize = QSize(5, 5);

Window::Window(QWidget* parent)
    : QMainWindow(parent)
{
    this->setupUi();
    this->setupObj();
}

Window::~Window()
{

}

void Window::setupUi()
{
    this->mainWidget = new QWidget(this);
    this->setCentralWidget(this->mainWidget);

    this->mainLayout = new QHBoxLayout(this->mainWidget);

    this->leftLayout = new QGridLayout(this->mainWidget);
    this->mainLayout->addLayout(this->leftLayout);

    this->leftLayoutLabel = new QLabel(this->mainWidget);
    this->leftLayoutLabel->setText(QString::fromWCharArray(L"Input image"));
    this->leftLayout->addWidget(this->leftLayoutLabel, 0, 0);
    this->leftLayout->setAlignment(this->leftLayoutLabel, Qt::AlignVCenter | Qt::AlignHCenter);

    this->drawer = new MarkedDrawer(imageSize, this->mainWidget);
    this->leftLayout->addWidget(this->drawer, 1, 0);
    this->leftLayout->setAlignment(this->drawer, Qt::AlignVCenter | Qt::AlignHCenter);

    this->leftButtonsLayout = new QHBoxLayout(this->mainWidget);
    this->leftLayout->addLayout(this->leftButtonsLayout, 2, 0);
    this->leftLayout->setAlignment(this->leftButtonsLayout, Qt::AlignVCenter | Qt::AlignHCenter);

    this->sampleButton = new QPushButton(this->mainWidget);
    this->sampleButton->setText(QString::fromWCharArray(L"Sample"));
    this->leftButtonsLayout->addWidget(this->sampleButton);

    this->recognizeButton = new QPushButton(this->mainWidget);
    this->recognizeButton->setText(QString::fromWCharArray(L"Recognize"));
    this->leftButtonsLayout->addWidget(this->recognizeButton);

    this->resultLabel = new QLabel(this->mainWidget);
    this->resultLabel->setText(QString::fromWCharArray(L"Result: null"));
    this->leftLayout->addWidget(this->resultLabel, 3, 0);
    this->leftLayout->setAlignment(this->resultLabel, Qt::AlignVCenter | Qt::AlignHCenter);

    this->rightLayout = new QVBoxLayout(this->mainWidget);
    this->mainLayout->addLayout(this->rightLayout);

    this->rightLayoutLabel = new QLabel(this->mainWidget);
    this->rightLayoutLabel->setText(QString::fromWCharArray(L"Samples"));
    this->rightLayout->addWidget(this->rightLayoutLabel);
    this->rightLayout->setAlignment(this->rightLayoutLabel, Qt::AlignTop | Qt::AlignHCenter);

    this->rightSamplesLayout = new QGridLayout(this->mainWidget);
    this->rightLayout->addLayout(this->rightSamplesLayout);
    this->rightLayout->setAlignment(this->rightSamplesLayout, Qt::AlignVCenter | Qt::AlignHCenter);

    this->clearButton = new QPushButton(this->mainWidget);
    this->clearButton->setText(QString::fromWCharArray(L"Clear"));
    this->rightLayout->addWidget(this->clearButton);
    this->rightLayout->setAlignment(this->clearButton, Qt::AlignBottom | Qt::AlignHCenter);
}

void Window::setupObj()
{
    this->samples = new QVector<MarkedDrawer*>();

    this->ai = new Hamming();
    this->ai->setImageSize(this->imageSize);

    connect(
        this->sampleButton, &QPushButton::clicked,
        this, [this]()
        {
            qDebug() << "Sample clicked.";

            this->ai->append(*this->drawer);

            this->samples->append(this->drawer);
            this->drawer = new MarkedDrawer(this->imageSize, this->mainWidget);
            this->leftLayout->addWidget(this->drawer, 1, 0);
            this->leftLayout->setAlignment(this->drawer, Qt::AlignVCenter | Qt::AlignHCenter);

            this->redrawSamples();
        }
    );

    connect(
        this->recognizeButton, &QPushButton::clicked,
        this, [this]()
        {
            qDebug() << "Recognize clicked.";

            auto result( this->ai->recognize(*this->drawer) );
            qDebug() << "Result is: " + result;

            this->resultLabel->setText(result);
        }
    );

    connect(
        this->clearButton, &QPushButton::clicked,
        this, [this]()
        {
            for (const auto sample : *samples)
            {
                delete sample;
            }
            samples->clear();

            this->redrawSamples();
        }
    );
}

void Window::redrawSamples()
{
    for (const auto widget : this->rightSamplesLayout->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly))
    {
        delete widget;
    }

    qint8 i = 0, j = 0;
    for (const auto& drawer : *samples)
    {
        this->rightSamplesLayout->addWidget(drawer, i, j);

        if(++j > 2)
        {
            ++i;
            j = 0;
        }
    }
}
