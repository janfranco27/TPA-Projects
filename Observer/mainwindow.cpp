#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    subject = Subject::Init();
    subject->addObserver(new GraphLine ());
    subject->addObserver(new GraphPoints ());

    std::vector <std::pair <double, double> > v;
    for (int i = 0; i < 5; i++)
    {
        v.push_back(std::make_pair(i*10,i*10));
    }
    subject->setState(v);
    subject->notify();
    ui->graphicsViewLine->setScene(subject->observers[0]->scene);
    ui->graphicsViewPoints->setScene(subject->observers[1]->scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_myTable_cellChanged(int row, int column)
{

}


void MainWindow::on_myTable_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"here";

    std::vector <std::pair <double, double> > v = subject->getState();

    if (item->column() == 0)
        v[item->row()].first = item->text().toDouble();
    else
        v[item->row()].second = item->text().toDouble();

    subject->setState(v);
    subject->notify();
    ui->graphicsViewLine->setScene(subject->observers[0]->scene);
    ui->graphicsViewPoints->setScene(subject->observers[1]->scene);
}
