#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <iostream>
#include "caretaker.h"
#include "circulo.h"
#include "cuadrado.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void redraw();
    void paintClicked(Figura* f);

private slots:
    void checkClickPosition(int x, int y);
    void receiveClick(int x, int y);
    void on_undoButton_clicked();

    void on_comboBColor_activated(int index);

    void on_sliderSize_valueChanged(int value);

    void on_redoButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    std::vector<Figura*> figuras;
    CareTaker careTaker;
};

#endif // MAINWINDOW_H
