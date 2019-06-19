#include "procesarimagen.h"

//Constructor
ProcesarImagen::ProcesarImagen(Mat imgOri, Mat imgBin, Mat imgSeg)
{
    imgOrigen = imgOri.clone();
    imgBinaria = imgBin.clone();
    imgSegmentada = imgSeg.clone();
}

ProcesarImagen::~ProcesarImagen()
{

}

// Funciones Pre-Procesamiento
void ProcesarImagen::canalAzul(Mat &imgOri, Mat &imgBlue)
{
    Mat chanel[3];
    Mat origen = imgOri.clone();

    // Dividir la imagen en canales de color
    split(origen,chanel);

    //Obtener en canal de Azul
    imgBlue = chanel[0];

}
