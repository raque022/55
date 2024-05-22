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
    ui->sideSize->setValidator( new QDoubleValidator(0, 1000, 2, this) );

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

    double tammannoLados = ui->sideSize->text().toDouble();

    QRectF viewRect = ui->graphicsView->viewport()->rect();


    ui->graphicsView->scene()->clear();


    double radioPX=((tammannoLados/(2* sin(M_PI/numLados)))*physicalDpiY()/2.54);
    double radioCM=(tammannoLados/(2* sin(M_PI/numLados)));

    double radioMaxPX=(viewRect.width()-10)/2;
    double radioMaxCM=((viewRect.width()-10)*2.54/(physicalDpiY()))/2;


    double factor=(radioMaxPX/radioPX);

    QPolygon polygon(numLados);

    for (int i = 0; i < numLados; ++i) {

        double angle = ((i * 2 * M_PI )/numLados);
        std::cout<<"i:"<<i<<"angulo: "<<angle;

        int x = factor*radioPX * cos(angle);

        int y = factor*radioPX * sin(angle);

        polygon[i]=(QPoint(x, y));

    }


    QRectF boundingRect = polygon.boundingRect();
    double scaleFactor = qMin((viewRect.width()-10) / boundingRect.width(),

                              (viewRect.height()-10)/ boundingRect.height());
    QTransform transform;

    transform.scale(scaleFactor, scaleFactor);

    //polygon= transform.map(polygon);


    scene->clear();

    scene->addPolygon(polygon);

    scene->setSceneRect(polygon.boundingRect());

    ui->labelScala->setText(QString("Escala 1 : %1 cm").arg(1/factor));
}
