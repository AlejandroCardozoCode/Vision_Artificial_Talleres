//Creado por Diego Alejadro Cardozo Rojas y Brayan Estiben Giraldo Lopez. Taller 2
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

cv::Mat piramideArriba(cv::Mat img1, int numero)
{
    cv::Mat imagenReducida, imagenAux;
    cv::Size size(img1.cols / 2, img1.rows / 2);
    imagenReducida = cv::Mat::zeros(size, CV_8UC1);
    cv::medianBlur(img1, imagenAux, 3);

    for (int i = 0; i < imagenReducida.rows; i++)
    {
        for (int j = 0; j < imagenReducida.cols; j++)
        {
            imagenReducida.at<uchar>(i, j) = imagenAux.at<uchar>(i * 2, j * 2);
        }
    }

    imwrite("gaussiana_" + std::to_string(numero) + ".png", imagenReducida);
    return imagenReducida;
}

cv::Mat piramideAbajo(cv::Mat img1, int numero)
{
    cv::Mat imagenReducida;
    cv::Size size(img1.cols * 2, img1.rows * 2);
    imagenReducida = cv::Mat::zeros(size, CV_8UC1);

    for (int i = 0; i < imagenReducida.rows; i++)
    {
        for (int j = 0; j < imagenReducida.cols; j++)
        {
            if ((i % 2 == 0) && (j % 2 == 0))
                imagenReducida.at<uchar>(i, j) = 0;
            else
                imagenReducida.at<uchar>(i, j) = img1.at<uchar>(i / 2, j / 2);
        }
    }

    cv::medianBlur(imagenReducida, imagenReducida, 3);
    imwrite("gaussiana_" + std::to_string(numero) + ".png", imagenReducida);
    return imagenReducida;
}

void laplaciana()
{
    std::string nombre = "gaussiana_";
    cv::Mat original, fuente, destino, siguienteAbajo, final;
    original = cv::imread(nombre + std::to_string(1) + ".png", 1);

    if (original.empty())
    {
        std::cout << "La imagen no se puedo abrir!\n"
                  << std::endl;
    }
    imwrite("laplaciana_" + std::to_string(1) + ".png", original);

    for (int i = 1; i < 7; i++)
    {
        fuente = cv::imread(nombre + std::to_string(i)+ ".png", 1);
        if (fuente.empty())
        {
            std::cout << "La imagen no se puedo abrir fuente!\n"
                      << std::endl;
        }
        siguienteAbajo = cv::imread(nombre + std::to_string(i + 1)+ ".png", 1);
        if (siguienteAbajo.empty())
        {
            std::cout << "La imagen no se puedo abrir abajo!\n"
                      << std::endl;
        }
        cv::Size size(fuente.cols * 2, fuente.rows * 2);
        cv::resize(fuente, destino, size);
        cv::subtract(destino, siguienteAbajo, final);
        imwrite("laplaciana_" + std::to_string(i + 1) + ".png", final);
    }
}

int main(int argc, char **argv)
{
    // Declare variables
    cv::Mat img1, arriba, abajo;
    cv::Mat kernel;
    cv::Point anchor;
    double delta;
    int ddepth;
    if(argc < 2)
    {
        std::cout << "error: por favor llame al programa de la manera: ./main <nombre_imagen>" << std::endl;
        exit(0);
    }

    img1 = cv::imread(argv[1], 1);
    if (img1.empty())
    {
        std::cout << "La imagen no se puedo abrir!\n"
                  << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }

    cv::cvtColor(img1, img1, cv::COLOR_BGR2GRAY);
    arriba = img1;
    abajo = img1;

    //impresion de las imagenes
    arriba = piramideArriba(arriba, 3);
    arriba = piramideArriba(arriba, 2);
    arriba = piramideArriba(arriba, 1);
    imwrite("gaussiana_" + std::to_string(4) + ".png", img1);
    abajo = piramideAbajo(abajo, 5);
    abajo = piramideAbajo(abajo, 6);
    abajo = piramideAbajo(abajo, 7);
    //llamado a la funcion que calcula las imagenes de laplace 
    laplaciana();
}