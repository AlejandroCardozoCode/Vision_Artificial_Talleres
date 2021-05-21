#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace cv;
using namespace std;

Mat src, copia;

struct Coordenadas
{
    int cX, cY, valor;
};

int valorRegion = 1;

vector<Coordenadas> colaDePixeles;

bool verificarPosicion(int x, int y)
{
    for (int i = 0; i < colaDePixeles.size(); i++)
    {
        if (colaDePixeles[i].cX == x && colaDePixeles[i].cY == y)
        {
            return false;
        }
    }
    return true;
}

void buscarRegion(Coordenadas punto)
{
    Coordenadas hijoArriba, hijoAbajo, hijoDer, hijoIzq;

    if ((punto.cY - 1) > 0)
    {
        hijoArriba.cX = punto.cX;
        hijoArriba.cY = punto.cY - 1;
        if ((int)src.at<uchar>(hijoArriba.cY, hijoArriba.cX) > 0 && verificarPosicion(hijoArriba.cX, hijoArriba.cY))
        {
            Coordenadas nuevo;
            nuevo.cX = hijoArriba.cX;
            nuevo.cY = hijoArriba.cY;
            nuevo.valor = valorRegion;

            colaDePixeles.push_back(nuevo);
            buscarRegion(nuevo);
        }
    }

    if ((punto.cY + 1) < src.rows)
    {
        hijoAbajo.cX = punto.cX;
        hijoAbajo.cY = punto.cY + 1;
        if ((int)src.at<uchar>(hijoAbajo.cY, hijoAbajo.cX) > 0 && verificarPosicion(hijoAbajo.cX, hijoAbajo.cY))
        {
            Coordenadas nuevo;
            nuevo.cX = hijoAbajo.cX;
            nuevo.cY = hijoAbajo.cY;
            nuevo.valor = valorRegion;

            colaDePixeles.push_back(nuevo);
            buscarRegion(nuevo);
        }
    }

    if ((punto.cX + 1) < src.cols)
    {
        hijoDer.cX = punto.cX + 1;
        hijoDer.cY = punto.cY;
        if ((int)src.at<uchar>(hijoDer.cY, hijoDer.cX) > 0 && verificarPosicion(hijoDer.cX, hijoDer.cY))
        {
            Coordenadas nuevo;
            nuevo.cX = hijoDer.cX;
            nuevo.cY = hijoDer.cY;
            nuevo.valor = valorRegion;

            colaDePixeles.push_back(nuevo);
            buscarRegion(nuevo);
        }
    }

    if ((punto.cX - 1) > 0)
    {
        hijoIzq.cX = punto.cX - 1;
        hijoIzq.cY = punto.cY;
        if ((int)src.at<uchar>(hijoIzq.cY, hijoIzq.cX) > 0 && verificarPosicion(hijoIzq.cX, hijoIzq.cY))
        {
            Coordenadas nuevo;
            nuevo.cX = hijoIzq.cX;
            nuevo.cY = hijoIzq.cY;
            nuevo.valor = valorRegion;

            colaDePixeles.push_back(nuevo);
            buscarRegion(nuevo);
        }
    }
    return;
}

void verificacionRegiones(Mat src)
{
    for (int i = 0; i < src.cols; i++)
    {
        for (int j = 0; j < src.rows; j++)
        {
            if ((int)src.at<uchar>(j, i) > 0 && verificarPosicion(i, j))
            {
                Coordenadas nuevo;
                nuevo.cX = i;
                nuevo.cY = j;
                nuevo.valor = valorRegion;

                colaDePixeles.push_back(nuevo);
                buscarRegion(nuevo);
                valorRegion++;
            }
        }
    }
}

int main(int argc, char *argv[])
{

    src = imread(argv[1], IMREAD_GRAYSCALE);
    if (src.empty())
    {
        cout << "No se puede abrir la imagen \n"
             << endl;
        return -1;
    }
    int contador = 1, intensidadImagen, cXAux, cYAux;
    float valorVariacionRegion;
    Size size(src.cols, src.rows);
    copia = Mat::zeros(size, CV_8UC1);

    cout << "Buscando Regiones en la imagen..." << endl;   

    for (int i = 0; i < src.cols; i++)
    {
        for (int j = 0; j < src.rows; j++)
        {
            if ((int)src.at<uchar>(j, i) > 0 && verificarPosicion(i, j))
            {
                Coordenadas nuevo;
                nuevo.cX = i;
                nuevo.cY = j;
                nuevo.valor = valorRegion;

                colaDePixeles.push_back(nuevo);
                buscarRegion(nuevo);
                valorRegion++;
            }
        }
    }
    valorVariacionRegion = 205 / valorRegion;
    intensidadImagen = 205;

    cout << "Generando imagen de Regiones Individuales etiquetadas..." << endl;

    while (contador <= valorRegion)
    {
        for (int i = 0; i < colaDePixeles.size(); i++)
        {
            if(colaDePixeles[i].valor == contador)
            {
                cXAux = colaDePixeles[i].cX;
                cYAux = colaDePixeles[i].cY;
                copia.at<uchar>(cYAux, cXAux) = intensidadImagen;
            }
        }
        contador ++;
        intensidadImagen = intensidadImagen - valorVariacionRegion;
    }

    imwrite("copia.png", copia);
}
