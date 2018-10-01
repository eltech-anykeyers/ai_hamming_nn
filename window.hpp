#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = Q_NULLPTR);
    ~Window();
};

#endif // WINDOW_HPP
