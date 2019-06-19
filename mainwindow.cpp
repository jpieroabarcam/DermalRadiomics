#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QImage>
#include <QString>

#include "procesarimagen/procesarimagen.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Variables Globales
const char path[]="/home/piero";

Mat original;
Mat binaria;
Mat segmentada;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ingresarButton_clicked()
{
    QString imagefilename = QFileDialog::getOpenFileName( this,"imagen.jpg", path,"Images (*.bmp *.png *.xpm *.jpg *.tif)");

    if(imagefilename == nullptr) return;

    Mat source = imread( imagefilename.toStdString());
    original = source.clone();
    Mat imgAzul;

    ProcesarImagen proc(original,binaria,segmentada);

    proc.canalAzul(original,imgAzul);
    imshow("Imagen Original",original);
    imshow("Imagen Binaria",imgAzul);

}
