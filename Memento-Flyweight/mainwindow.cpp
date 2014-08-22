#include "mainwindow.h"
#include "ui_mainwindow.h"

Memento* createMemento(std::vector<Figura*> figuras, Color circulo, Color cuadrado)
{
    Memento *m = new Memento(figuras, circulo, cuadrado);
    return m;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene ();
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
    connect(ui->graphicsView, SIGNAL (pointClicked(int,int)),this, SLOT(checkClickPosition(int,int)));

}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::redraw()
{
    scene->clear();
    for(size_t i = 0; i < figuras.size(); i++)
    {
       figuras[i]->draw(scene);
    }
    ui->graphicsView->setScene(scene);

}

void MainWindow::paintClicked(Figura *f)
{
}

void MainWindow::checkClickPosition (int x, int y)
{
    x = x - ui->sliderSize->value()/2;
    y = y - ui->sliderSize->value()/2;
    bool figureClicked = false;
    int i = 0;
    for (i = 0; i < figuras.size(); i++)
    {
        if (figuras[i]->wasClicked(x,y))
        {
            figureClicked = true;
            std::cout<<"Figura click " <<figuras[i]->getX()<<" "<<figuras[i]->getY()<<std::endl;
        }
    }

    if(figureClicked)
        paintClicked(figuras[i]);
    else
        receiveClick(x,y);
}

void MainWindow::receiveClick(int x, int y)
{
    std::cout<<"here "<<x<<" "<<y<<std::endl;

    Color selectedColor;
    if (ui->comboBColor->currentIndex() == rojo) selectedColor = rojo;
    else selectedColor = azul;
    bool shouldDraw = false;

    Figura *fig;
    if (ui->radioBCirculo->isChecked())
    {
        fig = new Circulo (x,y,selectedColor,ui->sliderSize->value(),circulo);
        shouldDraw = true;
    }
    else if (ui->radioBCuadrado->isChecked())
    {
        fig = new Cuadrado (x,y,selectedColor,ui->sliderSize->value(),cuadrado);
        shouldDraw = true;
    }
    std::cout<<ui->sliderSize->value()<<"  "<<"SLIDER"<<std::endl;
    if(shouldDraw)
    {
        figuras.push_back(fig);

        Color colorCirculo = rojo;
        Color colorCuadrado = rojo;
        int indice = -1;
        for(size_t i = 0; i < figuras.size(); i++)
        {
            if(figuras[i]->getTipo() == circulo)
            {
                indice = i;
                break;
            }
        }
        if(indice != -1)
            colorCirculo = figuras[indice]->getColor();

        indice = -1;
        for(size_t i = 0; i < figuras.size(); i++)
        {
            if(figuras[i]->getTipo() == cuadrado)
            {
                indice = i;
                break;
            }
        }
        if(indice != -1)
            colorCuadrado = figuras[indice]->getColor();


        careTaker.addMemento(createMemento(figuras, colorCirculo, colorCuadrado));
        redraw();
    }
}

void MainWindow::on_undoButton_clicked()
{
    figuras = careTaker.undo();
    redraw();
}

void MainWindow::on_comboBColor_activated(int index)
{
    int indice;

    if(figuras.size() > 0)
    {
        tipoFigura tipoFig;
        if (ui->radioBCirculo->isChecked()) tipoFig = circulo;
        else if (ui->radioBCuadrado->isChecked()) tipoFig = cuadrado;

        for(size_t i = 0; i < figuras.size(); i++)
        {
            if(figuras[i]->getTipo() == tipoFig)
            {
                indice = i;
                break;
            }
        }

        switch(index)
        {
            case 0:
                figuras[indice]->setColor(rojo);
                break;

            case 1:
                figuras[indice]->setColor(azul);
                break;
        }

        Color colorCirculo = rojo;
        Color colorCuadrado = rojo;
        int indice = -1;
        for(size_t i = 0; i < figuras.size(); i++)
        {
            if(figuras[i]->getTipo() == circulo)
            {
                indice = i;
                break;
            }
        }
        if(indice != -1)
            colorCirculo = figuras[indice]->getColor();

        indice = -1;
        for(size_t i = 0; i < figuras.size(); i++)
        {
            if(figuras[i]->getTipo() == cuadrado)
            {
                indice = i;
                break;
            }
        }
        if(indice != -1)
            colorCuadrado = figuras[indice]->getColor();


        careTaker.addMemento(createMemento(figuras, colorCirculo, colorCuadrado));
        redraw();

    }
}

void MainWindow::on_sliderSize_valueChanged(int value)
{
    int indice;

    if(figuras.size() > 0)
    {
        tipoFigura tipoFig;
        if (ui->radioBCirculo->isChecked()) tipoFig = circulo;
        else if (ui->radioBCuadrado->isChecked()) tipoFig = cuadrado;

        for(size_t i = 0; i < figuras.size(); i++)
        {
            if(figuras[i]->getTipo() == tipoFig)
            {
                indice = i;
                break;
            }
        }
        figuras[indice]->setRadio (value);
        redraw();
    }
}

void MainWindow::on_redoButton_clicked()
{
    if (careTaker.canRedo())
    {
        figuras = careTaker.redo();
        redraw();
    }
}
