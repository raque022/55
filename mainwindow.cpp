#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMainWindow>

#include <QGraphicsScene>
#include "QPolygonF"
#include <QGraphicsView>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)

        : QMainWindow(parent)

        , ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    


    scene = new QGraphicsScene(this);


    ui->graphicsView->setScene(scene);

    connect(ui->dibujarBtn, &QPushButton::clicked, this, &MainWindow::onDibujarClicked);


}


MainWindow::~MainWindow()

{

    delete ui;

}


void MainWindow::onDibujarClicked()

{

    int numLados = ui->numSidesSpinBox->value();

    double tammannoLados = ui->sideSizeSpinBox->value();

    QRectF viewRect = ui->graphicsView->viewport()->rect();


    // Clear the existing polygon

    ui->graphicsView->scene()->clear();


    double radio=(tammannoLados/(2* sin(M_PI/numLados)));

    double radioMax=((viewRect.width()-20) /(devicePixelRatio()/2.54))/2;
    double factor=radioMax/radio;

    std::cout<<"radio: "<<radio<<"\n";

    QPolygon polygon(numLados);

    for (int i = 0; i < numLados; ++i) {

        double angle = ((i * 2 * M_PI )/numLados);
        std::cout<<"i:"<<i<<"angulo: "<<angle;

        int x = qIntCast(factor) * radio * cos(angle);

        int y = qIntCast(factor) * radio * sin(angle);

        polygon[i]=(QPoint(x, y));

    }
    // Scale the polygon to fit in the view

    QRectF boundingRect = polygon.boundingRect();

    double scaleFactor = qMin((viewRect.width()-20) / boundingRect.width(),

                              (viewRect.height()-20)/ boundingRect.height());
    QTransform transform;

    transform.scale(scaleFactor, scaleFactor); // Set the scale factor

    polygon= transform.map(polygon);

    // Draw the polygon in the view

    scene->clear();

    scene->addPolygon(polygon);

    scene->setSceneRect(polygon.boundingRect());

    ui->labelScala->setText(QString("Escala 1:%1 cm").arg(1/factor));
}