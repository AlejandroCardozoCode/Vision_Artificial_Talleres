
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
Mat original, escalaGrises, imagenHsv, hue, bordesImagen;
int bins = 12;

static void bordes()
{
    int lowThreshold = 35;
    const int ratio = 3;
    const int tamKernel = 3;
    blur(escalaGrises, bordesImagen, Size(3, 3));
    Canny(bordesImagen, bordesImagen, lowThreshold, lowThreshold * ratio, tamKernel);
    imwrite("Bordes.png", bordesImagen);
}

void intensidades()
{
    int histSize = MAX(bins, 0);
    float rango[] = {0, 180};
    const float *rangos = {rango};
    Mat histograma, final;
    calcHist(&hue, 1, 0, Mat(), histograma, 1, &histSize, &rangos, true, false);
    normalize(histograma, histograma, 0, 255, NORM_MINMAX, -1, Mat());
    calcBackProject(&hue, 1, 0, histograma, final, &rangos, 1, true);

    imwrite("intensidades.png", final);
}

int main(int argc, char *argv[])
{
    original = imread(argv[1], IMREAD_COLOR); 
    if (original.empty())
    {
        std::cout << "No se puedo abrir el archivo de la imagen\n"<< std::endl;
        return -1;
    }
    cvtColor(original, escalaGrises, COLOR_BGR2GRAY);
    cvtColor(original, imagenHsv, COLOR_BGR2HSV);
    hue.create(imagenHsv.size(), imagenHsv.depth());
    int canales[] = {0, 0};
    mixChannels(&imagenHsv, 1, &hue, 1, canales, 1);

    bordes();
    intensidades();
    return 0;
}
