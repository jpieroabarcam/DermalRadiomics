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

// funciones privadas
int ProcesarImagen::computeOutput(int x, int r1, int s1, int r2, int s2)
{
    float result;
    if(0 <= x && x <= r1){
        result = s1/r1 * x;
    }else if(r1 < x && x <= r2){
        result = ((s2 - s1)/(r2 - r1)) * (x - r1) + s1;
    }else if(r2 < x && x <= 255){
        result = ((255 - s2)/(255 - r2)) * (x - r2) + s2;
    }
    return (int)result;
}

// Funciones Mejoramiento de imagen
void ProcesarImagen::contrastStretching(Mat &dst, Mat &imgConstrast) {

    int r1, s1, r2, s2;
    r1 = 90;
    s1 = 150;
    r2 = 100;
    s2 = 255;

    for(int y = 0; y < dst.rows; y++){
        for(int x = 0; x < dst.cols; x++){
            for(int c = 0; c < 3; c++){
                int output = computeOutput(dst.at<Vec3b>(y,x)[c], r1, s1, r2, s2);
                imgConstrast.at<cv::Vec3b>(y,x)[c] = cv::saturate_cast<uchar>(output);
            }
        }
     }
}

void ProcesarImagen::clahe(Mat &dst, Mat &imgClahe) {

    Mat lab_image;
    cvtColor(dst, lab_image, COLOR_BGR2Lab);

    // Extract the L channel
    vector<Mat> lab_planes(3);
    split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

    // apply the CLAHE algorithm to the L channel
    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(4);
    Mat result;
    clahe->apply(lab_planes[0], result);

    // Merge the the color planes back into an Lab image
    result.copyTo(lab_planes[0]);
    merge(lab_planes, lab_image);

    // convert back to RGB
    cvtColor(lab_image, imgClahe,COLOR_Lab2BGR);
}

void ProcesarImagen::histogramEqualization(Mat &dst, Mat &imgHistEq) {
    //change the color image to grayscale image
    Mat imgGrayScale;
    cvtColor(dst, imgGrayScale, COLOR_BGR2GRAY);

    //equalize the histogram
    equalizeHist(imgGrayScale, imgHistEq);
}

void ProcesarImagen::histogramEqualizationColor(Mat &dst, Mat &imgHistEqCol) {
    //Convert the image from BGR to YCrCb color space
    cvtColor(dst, imgHistEqCol, COLOR_BGR2YCrCb);

    //Split the image into 3 channels; Y, Cr and Cb channels respectively and store it in a std::vector
    vector<Mat> vec_channels;
    split(imgHistEqCol, vec_channels);

    //Equalize the histogram of only the Y channel
    equalizeHist(vec_channels[0], vec_channels[0]);

    //Merge 3 channels in the vector to form the color image in YCrCB color space.
    merge(vec_channels, imgHistEqCol);

    //Convert the histogram equalized image from YCrCb to BGR color space again
    cvtColor(imgHistEqCol, imgHistEqCol, COLOR_YCrCb2BGR);
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


// segmentacion de imagen
void ProcesarImagen::metodoOtsu(Mat &blue, Mat &dst)
{
    //procesar la imagen pasar a limites de 0 a 255
    threshold(blue,dst,0,255,THRESH_BINARY|THRESH_OTSU);
    //invertir los colores
    dst = ~dst;
}

void ProcesarImagen::fillHoles(Mat &dst)
{
    //se asume que la entrada es imagen Blanco y Negro(0 or 255)
    Mat holes=dst.clone();
    floodFill(holes,cv::Point2i(0,0),cv::Scalar(255));
    for(int i=0;i<dst.rows*dst.cols;i++)
    {
        if(holes.data[i]==0)
            dst.data[i]=255;
    }
}
