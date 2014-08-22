#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "subject.h"
#include "graphline.h"
#include "graphpoints.h"
#include <QTableWidgetItem>
#include <iostream>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_myTable_cellChanged(int row, int column);

    void on_myTable_itemChanged(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Subject* subject;
};

#endif // MAINWINDOW_H
