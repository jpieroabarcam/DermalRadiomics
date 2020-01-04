#ifndef PROCESARIMAGEN_H
#define PROCESARIMAGEN_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/core/core.hpp>
#include "opencv2/core/utility.hpp"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class ProcesarImagen
{
private:
    Mat imgOrigen;
    Mat imgBinaria;
    Mat imgSegmentada;

    // Enhance image
    int computeOutput(int, int, int, int, int);

public:
    ProcesarImagen(Mat,Mat,Mat);
    virtual ~ProcesarImagen();
    // Mejorar Imagen
    void contrastStretching(Mat&,Mat&);
    void histogramEqualization(Mat&, Mat&);
    void histogramEqualizationColor(Mat&, Mat&);
    void clahe(Mat&,Mat&);

    // Pre Procesamiento
    void canalAzul(Mat&,Mat&);
    void metodoOtsu(Mat&,Mat&);
    void fillHoles(Mat&);
};

#endif // PROCESARIMAGEN_H
