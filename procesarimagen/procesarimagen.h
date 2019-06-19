#ifndef PROCESARIMAGEN_H
#define PROCESARIMAGEN_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

class ProcesarImagen
{
private:
    Mat imgOrigen;
    Mat imgBinaria;
    Mat imgSegmentada;

public:
    ProcesarImagen(Mat,Mat,Mat);
    virtual ~ProcesarImagen();
    // Pre Procesamiento
    void canalAzul(Mat&,Mat&);
    void metodoOtzu(Mat&,Mat&);
};

#endif // PROCESARIMAGEN_H
