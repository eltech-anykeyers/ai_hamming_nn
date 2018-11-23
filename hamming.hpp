#ifndef HAMMING_HPP
#define HAMMING_HPP

#include <QPair>
#include <QSize>
#include <QVector>

#include <grid_drawer/marked_drawer.hpp>

class Hamming
{
public:
    Hamming();

    void append(const MarkedDrawer& image);
    QString recognize(const MarkedDrawer& image);

    qint32 getImageLinearSize() const;
    void setLinearSize(const qint32 imageLinearSize);

    QSize getImageSize() const;
    void setImageSize(const QSize& imageSize);

    void clear();

private:
    static const double epsilon;

    QSize imageSize;
    qint32 imageLinearSize; // image_size.width * image_size.height;

    double randomShittyParameter; // image_linear_size / 2.0;

    QVector<QPair<QString, QVector<double>*>*>* samplesMatrix;
    QVector<QVector<double>*>* weightsMatrix;
    QVector<QVector<double>*>* feedbackMatrix;

    void updateWeightsMatrix();
    void updateFeedbackMatrix();

    inline double activation(double arg) const;

    inline double norm(const QVector<double>& vector) const;
};

#endif // HAMMING_HPP
