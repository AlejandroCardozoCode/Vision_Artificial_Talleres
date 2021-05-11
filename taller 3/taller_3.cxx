
/*----------------------------------------------------------------
taller 3 programado por alejandro cardozo y brayan giraldo 
*/

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace cv;
using namespace std;

struct Posi
{
    int cX, cY;
};

struct Hijos
{
    int cX, cY;
    vector<int> vecinos;
};

vector<Posi> posicionesGuardadas;

bool verificacion(int x, int y)
{
    for (int i = 0; i < posicionesGuardadas.size(); i++)
    {
        if (posicionesGuardadas[i].cX == x && posicionesGuardadas[i].cY == y)
        {
            return false;
        }
    }
    return true;
}

bool verificarIntensidad(int umbralMayor, int intensidadPixel, int umbralMenor)
{
    if (intensidadPixel <= umbralMayor && intensidadPixel >= umbralMenor)
    {
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    Mat src, src_gray, imgNueva, imagenColor;
    int corX /*filas*/, corY /*col*/, tolerancia, vecinos, hijos, intensidadOriginal = 0, opcion;
    vector<Hijos> arregloHijos;

    src = imread(argv[1], 1);
    if (src.empty())
    {
        cout << "No se puede abrir la imagen \n"
             << endl;
        return -1;
    }
    Size size2(src.cols, src.rows);
    imagenColor = Mat::zeros(size2, CV_8UC3);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    cout << "Para la generacion de una semilla automatica ingrese 1, si la desea ingresar manuealmente ingrese 0: ";
    cin >> opcion;
    if (opcion == 0)
    {
        cout << "Ingrese la coordenada en x: ";
        cin >> corX;
        cout << endl;
        cout << "Ingrese la coordenada en y: ";
        cin >> corY;
        cout << endl;
        cout << "Ingrese el grado de tolerancia: ";
        cin >> tolerancia;
        cout << endl;
        intensidadOriginal = (int)src_gray.at<uchar>(corX, corY);
    }
    else if(opcion == 1)
    {
        for (int i = 0; i < src_gray.rows; i++)
        {
            for (int j = 0; j < src_gray.cols; j++)
            {
                if ((int)src_gray.at<uchar>(i, j) > intensidadOriginal)
                {
                    intensidadOriginal = (int)src_gray.at<uchar>(i, j);
                    corX = i;
                    corY = j;
                }
            }
        }
        
        cout << "Semilla generada automaticamente con la mayor intencidad de la imagen, coordenadas x: " << corX << ", y: " << corY << endl;
        cout << "Ingrese el grado de tolerancia: ";
        cin >> tolerancia;
        cout << endl;
    }

    
    Size size(src_gray.cols, src_gray.rows);
    imgNueva = Mat::zeros(size, CV_8UC1);
    Hijos aux;
    aux.cX = corX;
    aux.cY = corY;
    //arriba vecino

    if ((aux.cY - 1) < imgNueva.cols && (aux.cY - 1) > 0)
    {
        if (verificacion(aux.cX, aux.cY - 1))
        {
            aux.vecinos.push_back(aux.cX);
            aux.vecinos.push_back(aux.cY - 1);
        }
    }
    //abajo vecino
    if ((aux.cY + 1) < imgNueva.cols && (aux.cY + 1) > 0)
    {
        if (verificacion(aux.cX, aux.cY + 1))
        {
            aux.vecinos.push_back(aux.cX);
            aux.vecinos.push_back(aux.cY + 1);
        }
    }
    //derecha vecino
    if ((aux.cX + 1) < imgNueva.rows && (aux.cX + 1) > 0)
    {
        if (verificacion(aux.cX + 1, aux.cY))
        {
            aux.vecinos.push_back(aux.cX + 1);
            aux.vecinos.push_back(aux.cY);
        }
    }
    //izquierda vecino
    if ((aux.cX + 1) < imgNueva.rows && (aux.cX + 1) > 0)
    {
        if (verificacion(aux.cX - 1, aux.cY))
        {
            aux.vecinos.push_back(aux.cX - 1);
            aux.vecinos.push_back(aux.cY);
        }
    }

    Posi aux3;
    aux3.cX = aux.cX;
    aux3.cY = aux.cY;
    if (verificacion(aux.cX, aux.cY))
    {
        posicionesGuardadas.push_back(aux3);
        arregloHijos.push_back(aux);
    }
    system("clear");
    cout << "procesando la imagen por favor espere (este proceso puede tomar un tiempo si la imagen es muy grande o el grado de tolerancia es muy amplio)" << endl;
    while (!arregloHijos.empty())
    {
        int i = 0;
        vector<int> auxVecinos = arregloHijos[0].vecinos;
        while (!auxVecinos.empty())
        {
            int intensidadPixel = (int)src_gray.at<uchar>(auxVecinos[0], auxVecinos[1]);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                imgNueva.at<uchar>(auxVecinos[0], auxVecinos[1]) = 255;
                imagenColor.at<Vec3b>(auxVecinos[0], auxVecinos[1]) = src.at<Vec3b>(auxVecinos[0], auxVecinos[1]);
            }
            auxVecinos.erase(auxVecinos.begin());
            auxVecinos.erase(auxVecinos.begin());
        }
        if ((arregloHijos[i].cY - 1) < imgNueva.cols && (arregloHijos[i].cY - 1) > 0)
        {
            int intensidadPixel = (int)src_gray.at<uchar>(arregloHijos[i].cX, arregloHijos[i].cY - 1);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                Hijos arriba;
                arriba.cX = arregloHijos[i].cX;
                arriba.cY = arregloHijos[i].cY - 1;

                //arriba vecino
                if ((arriba.cY - 1) < imgNueva.cols && (arriba.cY - 1) > 0)
                {

                    if (verificacion(arriba.cX, arriba.cY - 1))
                    {
                        arriba.vecinos.push_back(arriba.cX);
                        arriba.vecinos.push_back(arriba.cY - 1);
                    }
                }
                //derecha vecino
                if ((arriba.cX + 1) < imgNueva.rows && (arriba.cX + 1) > 0)
                {
                    if (verificacion(arriba.cX + 1, arriba.cY))
                    {
                        arriba.vecinos.push_back(arriba.cX + 1);
                        arriba.vecinos.push_back(arriba.cY);
                    }
                }
                //izquierda vecino
                if ((arriba.cX + 1) < imgNueva.rows && (arriba.cX + 1) > 0)
                {
                    if (verificacion(arriba.cX - 1, arriba.cY))
                    {
                        arriba.vecinos.push_back(arriba.cX - 1);
                        arriba.vecinos.push_back(arriba.cY);
                    }
                }
                Posi aux3;
                aux3.cX = arriba.cX;
                aux3.cY = arriba.cY;
                if (verificacion(arriba.cX, arriba.cY))
                {
                    posicionesGuardadas.push_back(aux3);
                    arregloHijos.push_back(arriba);
                }
            }
        }
        if ((arregloHijos[i].cY + 1) < imgNueva.cols && (arregloHijos[i].cY + 1) > 0)
        {
            int intensidadPixel = (int)src_gray.at<uchar>(arregloHijos[i].cX, arregloHijos[i].cY + 1);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                Hijos abajo;
                abajo.cX = arregloHijos[i].cX;
                abajo.cY = arregloHijos[i].cY + 1;

                //abajo vecino
                if ((abajo.cY + 1) < imgNueva.cols && (abajo.cY + 1) > 0)
                {
                    if (verificacion(abajo.cX, abajo.cY + 1))
                    {
                        abajo.vecinos.push_back(abajo.cX);
                        abajo.vecinos.push_back(abajo.cY + 1);
                    }
                }
                //derecha vecino
                if ((abajo.cX + 1) < imgNueva.rows && (abajo.cX + 1) > 0)
                {
                    if (verificacion(abajo.cX + 1, abajo.cY))
                    {
                        abajo.vecinos.push_back(abajo.cX + 1);
                        abajo.vecinos.push_back(abajo.cY);
                    }
                }
                //izquierda vecino
                if ((abajo.cX + 1) < imgNueva.rows && (abajo.cX + 1) > 0)
                {
                    if (verificacion(abajo.cX - 1, abajo.cY))
                    {
                        abajo.vecinos.push_back(abajo.cX - 1);
                        abajo.vecinos.push_back(abajo.cY);
                    }
                }
                Posi aux3;
                aux3.cX = abajo.cX;
                aux3.cY = abajo.cY;
                if (verificacion(abajo.cX, abajo.cY))
                {
                    posicionesGuardadas.push_back(aux3);
                    arregloHijos.push_back(abajo);
                }
            }
        }

        if ((arregloHijos[i].cX + 1) < imgNueva.rows && (arregloHijos[i].cX + 1) > 0)
        {
            int intensidadPixel = (int)src_gray.at<uchar>(arregloHijos[i].cX + 1, arregloHijos[i].cY);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                Hijos derecha;
                derecha.cX = arregloHijos[i].cX + 1;
                derecha.cY = arregloHijos[i].cY;

                //arriba vecino
                if ((derecha.cY - 1) < imgNueva.cols && (derecha.cY - 1) > 0)
                {
                    if (verificacion(derecha.cX, derecha.cY - 1))
                    {
                        derecha.vecinos.push_back(derecha.cX);
                        derecha.vecinos.push_back(derecha.cY - 1);
                    }
                }
                //abajo vecino
                if ((derecha.cY + 1) < imgNueva.cols && (derecha.cY + 1) > 0)
                {
                    if (verificacion(derecha.cX, derecha.cY + 1))
                    {
                        derecha.vecinos.push_back(derecha.cX);
                        derecha.vecinos.push_back(derecha.cY + 1);
                    }
                }
                //derecha vecino
                if ((derecha.cX + 1) < imgNueva.rows && (derecha.cX + 1) > 0)
                {
                    if (verificacion(derecha.cX + 1, derecha.cY))
                    {
                        derecha.vecinos.push_back(derecha.cX + 1);
                        derecha.vecinos.push_back(derecha.cY);
                    }
                }

                Posi aux3;
                aux3.cX = derecha.cX;
                aux3.cY = derecha.cY;
                if (verificacion(derecha.cX, derecha.cY))
                {
                    posicionesGuardadas.push_back(aux3);
                    arregloHijos.push_back(derecha);
                }
            }
        }
        if ((arregloHijos[i].cX - 1) < imgNueva.rows && (arregloHijos[i].cX - 1) > 0)
        {
            int intensidadPixel = (int)src_gray.at<uchar>(arregloHijos[i].cX - 1, arregloHijos[i].cY);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                Hijos izquierda;
                izquierda.cX = arregloHijos[i].cX - 1;
                izquierda.cY = arregloHijos[i].cY;

                //arriba vecino
                if ((izquierda.cY - 1) < imgNueva.cols && (izquierda.cY - 1) > 0)
                {
                    if (verificacion(izquierda.cX, izquierda.cY - 1))
                    {
                        izquierda.vecinos.push_back(izquierda.cX);
                        izquierda.vecinos.push_back(izquierda.cY - 1);
                    }
                }
                //abajo vecino
                if ((izquierda.cY + 1) < imgNueva.cols && (izquierda.cY + 1) > 0)
                {
                    if (verificacion(izquierda.cX, izquierda.cY + 1))
                    {
                        izquierda.vecinos.push_back(izquierda.cX);
                        izquierda.vecinos.push_back(izquierda.cY + 1);
                    }
                }

                //izquierda vecino
                if ((izquierda.cX + 1) < imgNueva.rows && (izquierda.cX + 1) > 0)
                {
                    if (verificacion(izquierda.cX - 1, izquierda.cY))
                    {
                        izquierda.vecinos.push_back(izquierda.cX - 1);
                        izquierda.vecinos.push_back(izquierda.cY);
                    }
                }
                Posi aux3;
                aux3.cX = izquierda.cX;
                aux3.cY = izquierda.cY;
                if (verificacion(izquierda.cX, izquierda.cY))
                {
                    posicionesGuardadas.push_back(aux3);
                    arregloHijos.push_back(izquierda);
                }
            }
        }
        arregloHijos.erase(arregloHijos.begin());
    }

    cout << "Termino el procesamiento de la imagen" << endl;

    imwrite("imagen_etiquetada.png", imgNueva);
    imwrite("imagen_segmentada.png", imagenColor);
}
