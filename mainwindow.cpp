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
    QString imagefilename = QFileDialog::getOpenFileName( this,"imagen.jpg", path,"Images (*.bmp *.png *.xpm *.jpg *.jpeg *.tif)");

    if(imagefilename == nullptr) return;

    Mat source = imread( imagefilename.toStdString());
    original = source.clone();
    Mat imgAzul;    
    Mat imgOrigen;
    Mat imgContrast;

    ProcesarImagen proc(original,binaria,segmentada);

    imgOrigen = original.clone();
    imgContrast = original.clone();

    proc.contrastStretching(imgOrigen,imgContrast);
    //proc.clahe(imgOrigen, imgContrast);

    imshow("origen",imgOrigen);
    imshow("contrast Stretching",imgContrast);

    proc.canalAzul(imgContrast,imgAzul);

    proc.metodoOtsu(imgAzul,imgOrigen);
    proc.fillHoles(imgOrigen);

    imshow("Canal Azul",imgAzul);
    imshow("Otsu",imgOrigen);


}
