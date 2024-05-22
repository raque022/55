#ifndef MAINWINDOW_H

#define MAINWINDOW_H


#include <QMainWindow>

#include <QGraphicsScene>

#include <QGraphicsView>
#include <QLabel>


QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }

QT_END_NAMESPACE


class MainWindow : public QMainWindow

{

Q_OBJECT


public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private slots:

    void onDibujarClicked();



private:

    Ui::MainWindow *ui;
    QPolygon polygon;
    QLabel* labelScala;
    QGraphicsView* graphicsView;
    QGraphicsView* polygonView;
    QGraphicsScene *scene;

};

#endif // MAINWINDOW_H
