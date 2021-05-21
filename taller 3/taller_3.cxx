
/*----------------------------------------------------------------
taller 3 programado por alejandro cardozo y brayan giraldo 
*/
/* ADICIONALES 

- RECIBIR IMAGENES EN COLOR
-SELSECCION AUTOMATICA DE SEMILLA (INTENSIDAD MAS ALTA)
- DESVIACION ESTANDAR DE LOS VECINOS DE LA SEMILLA 
- VECINDARIO 8 VECINOS 
- RESULTADO COMO IMAGEN SEGMENTADA UMBRALIZADA 

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
    int corX /*filas*/, corY /*col*/, tolerancia, vecinos, hijos, intensidadOriginal = 0, opcion, toleranciaVecinos = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 8, t7 = 0, t8 = 0;
    float totalT = 0;
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
    Size size(src_gray.cols, src_gray.rows);

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
        intensidadOriginal = (int)src_gray.at<uchar>(corY, corX);
    }
    else if (opcion == 1)
    {
        for (int i = 0; i < src_gray.cols; i++)
        {
            for (int j = 0; j < src_gray.rows; j++)
            {
                if ((int)src_gray.at<uchar>(j, i) > intensidadOriginal)
                {
                    intensidadOriginal = (int)src_gray.at<uchar>(j, i);
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

    

    if (corX < 0 || corX > src_gray.cols)
    {
        cout << "la cordeenada de x no es valida "  << endl;
        return -1;
    }
    if (corY < 0 || corY > src_gray.rows)
    {
        cout << "la cordeenada de y no es valida "  << endl;
        return -1;
    }
    

    
    imgNueva = Mat::zeros(size, CV_8UC1);
    Hijos aux;
    aux.cX = corX;
    aux.cY = corY;
    //arriba vecino

    if ((aux.cY - 1) < imgNueva.rows && (aux.cY - 1) > 0)
    {
        if (verificacion(aux.cX, aux.cY - 1))
        {
            aux.vecinos.push_back(aux.cX);
            aux.vecinos.push_back(aux.cY - 1);
            toleranciaVecinos = toleranciaVecinos + (int)src_gray.at<uchar>(aux.cY -1, aux.cX);
            t1 = (int)src_gray.at<uchar>(aux.cY-1, aux.cX );
        }
    }
    //abajo vecino
    if ((aux.cY + 1) < imgNueva.rows && (aux.cY + 1) > 0)
    {
        if (verificacion(aux.cX, aux.cY + 1))
        {
            aux.vecinos.push_back(aux.cX);
            aux.vecinos.push_back(aux.cY + 1);
            toleranciaVecinos = toleranciaVecinos + (int)src_gray.at<uchar>(aux.cY + 1, aux.cX);
            t2 = (int)src_gray.at<uchar>(aux.cY + 1, aux.cX);
        }
    }
    //derecha vecino
    if ((aux.cX + 1) < imgNueva.cols && (aux.cX + 1) > 0)
    {
        if (verificacion(aux.cX + 1, aux.cY))
        {
            aux.vecinos.push_back(aux.cX + 1);
            aux.vecinos.push_back(aux.cY);
            toleranciaVecinos = toleranciaVecinos + (int)src_gray.at<uchar>(aux.cY, aux.cX + 1);
            t3 = (int)src_gray.at<uchar>(aux.cY, aux.cX + 1);
        }
    }
    //izquierda vecino
    if ((aux.cX + 1) < imgNueva.cols && (aux.cX + 1) > 0)
    {
        if (verificacion(aux.cX - 1, aux.cY))
        {
            aux.vecinos.push_back(aux.cX - 1);
            aux.vecinos.push_back(aux.cY);
            toleranciaVecinos = toleranciaVecinos + (int)src_gray.at<uchar>(aux.cY, aux.cX + 1);
            t4 = (int)src_gray.at<uchar>(aux.cY, aux.cX + 1);
        }
    }

    //diagonales

    //arriba derecha

    if ((aux.cY - 1) < imgNueva.rows && (aux.cY - 1) > 0 && (aux.cX + 1) < imgNueva.rows && (aux.cX + 1) > 0)
    {
        if (verificacion(aux.cX + 1, aux.cY - 1))
        {
            aux.vecinos.push_back(aux.cX + 1);
            aux.vecinos.push_back(aux.cY - 1);
            toleranciaVecinos = toleranciaVecinos + (int)src_gray.at<uchar>(aux.cY - 1, aux.cX + 1);
            t5 = (int)src_gray.at<uchar>(aux.cY - 1, aux.cX + 1);
        }
    }
    //abajo izq
    if ((aux.cY - 1) < imgNueva.rows && (aux.cY - 1) > 0 && (aux.cX - 1) < imgNueva.rows && (aux.cX - 1) > 0)
    {
        if (verificacion(aux.cX - 1, aux.cY - 1))
        {
            aux.vecinos.push_back(aux.cX - 1);
            aux.vecinos.push_back(aux.cY - 1);
            toleranciaVecinos = toleranciaVecinos + (int)src_gray.at<uchar>(aux.cY - 1, aux.cX - 1);
            t6 = (int)src_gray.at<uchar>(aux.cY - 1, aux.cX - 1);
        }
    }
    //abajo derecha
    if ((aux.cY + 1) < imgNueva.rows && (aux.cY + 1) > 0 && (aux.cX + 1) < imgNueva.rows && (aux.cX + 1) > 0)
    {
        if (verificacion(aux.cX + 1, aux.cY + 1))
        {
            aux.vecinos.push_back(aux.cX + 1);
            aux.vecinos.push_back(aux.cY + 1);
            toleranciaVecinos = toleranciaVecinos + (int)src_gray.at<uchar>(aux.cY + 1, aux.cX + 1);
            t7 = (int)src_gray.at<uchar>(aux.cY + 1, aux.cX + 1);
        }
    }
    //abajo izq
    if ((aux.cY + 1) < imgNueva.rows && (aux.cY + 1) > 0 && (aux.cX - 1) < imgNueva.rows && (aux.cX - 1) > 0)
    {
        if (verificacion(aux.cX - 1, aux.cY + 1))
        {
            aux.vecinos.push_back(aux.cX - 1);
            aux.vecinos.push_back(aux.cY + 1);
            toleranciaVecinos = toleranciaVecinos + (int)src_gray.at<uchar>(aux.cY + 1, aux.cX - 1);
            t8 = (int)src_gray.at<uchar>(aux.cY + 1, aux.cX - 1);
        }
    }

    t1 = (t1 - (toleranciaVecinos / 8)) * (t1 - (toleranciaVecinos / 8));
    t2 = (t2 - (toleranciaVecinos / 8)) * (t2 - (toleranciaVecinos / 8));
    t3 = (t3 - (toleranciaVecinos / 8)) * (t3 - (toleranciaVecinos / 8));
    t4 = (t4 - (toleranciaVecinos / 8)) * (t4 - (toleranciaVecinos / 8));
    t5 = (t5 - (toleranciaVecinos / 8)) * (t5 - (toleranciaVecinos / 8));
    t6 = (t6 - (toleranciaVecinos / 8)) * (t6 - (toleranciaVecinos / 8));
    t7 = (t7 - (toleranciaVecinos / 8)) * (t7 - (toleranciaVecinos / 8));
    t8 = (t8 - (toleranciaVecinos / 8)) * (t8 - (toleranciaVecinos / 8));
    system("clear");
    totalT = sqrt((t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8) / 8);

    cout << "El promedio del vecindario de la semilla es: " << toleranciaVecinos / 8 << endl;
    cout << "La desviacion estandar del vecindario de la semilla es: " << totalT << endl;
    Posi aux3;
    aux3.cX = aux.cX;
    aux3.cY = aux.cY;
    if (verificacion(aux.cX, aux.cY))
    {
        posicionesGuardadas.push_back(aux3);
        arregloHijos.push_back(aux);
    }

    cout << "procesando la imagen por favor espere (este proceso puede tomar un tiempo si la imagen es muy grande o el grado de tolerancia es muy amplio)" << endl;
    while (!arregloHijos.empty())
    {
        int i = 0;
        vector<int> auxVecinos = arregloHijos[0].vecinos;
        while (!auxVecinos.empty())
        {
            int intensidadPixel = (int)src_gray.at<uchar>(auxVecinos[1], auxVecinos[0]);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                imgNueva.at<uchar>(auxVecinos[1], auxVecinos[0]) = 255;
                imagenColor.at<Vec3b>(auxVecinos[1], auxVecinos[0]) = src.at<Vec3b>(auxVecinos[1], auxVecinos[0]);
            }
            auxVecinos.erase(auxVecinos.begin());
            auxVecinos.erase(auxVecinos.begin());
        }
        if ((arregloHijos[i].cY - 1) < imgNueva.rows && (arregloHijos[i].cY - 1) > 0)
        {
            int intensidadPixel = (int)src_gray.at<uchar>(arregloHijos[i].cY - 1, arregloHijos[i].cX);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                Hijos arriba;
                arriba.cX = arregloHijos[i].cX;
                arriba.cY = arregloHijos[i].cY - 1;

                //arriba vecino
                if ((arriba.cY - 1) < imgNueva.rows && (arriba.cY - 1) > 0)
                {

                    if (verificacion(arriba.cX, arriba.cY - 1))
                    {
                        arriba.vecinos.push_back(arriba.cX);
                        arriba.vecinos.push_back(arriba.cY - 1);
                    }
                }
                //derecha vecino
                if ((arriba.cX + 1) < imgNueva.cols && (arriba.cX + 1) > 0)
                {
                    if (verificacion(arriba.cX + 1, arriba.cY))
                    {
                        arriba.vecinos.push_back(arriba.cX + 1);
                        arriba.vecinos.push_back(arriba.cY);
                    }
                }
                //izquierda vecino
                if ((arriba.cX + 1) < imgNueva.cols && (arriba.cX + 1) > 0)
                {
                    if (verificacion(arriba.cX - 1, arriba.cY))
                    {
                        arriba.vecinos.push_back(arriba.cX - 1);
                        arriba.vecinos.push_back(arriba.cY);
                    }
                }

                //diagonales

                //arriba derecha

                if ((arriba.cY - 1) < imgNueva.rows && (arriba.cY - 1) > 0 && (arriba.cX + 1) < imgNueva.rows && (arriba.cX + 1) > 0)
                {
                    if (verificacion(arriba.cX + 1, arriba.cY - 1))
                    {
                        arriba.vecinos.push_back(arriba.cX + 1);
                        arriba.vecinos.push_back(arriba.cY - 1);
                    }
                }
                //abajo izq
                if ((arriba.cY - 1) < imgNueva.rows && (arriba.cY - 1) > 0 && (arriba.cX - 1) < imgNueva.rows && (arriba.cX - 1) > 0)
                {
                    if (verificacion(arriba.cX - 1, arriba.cY - 1))
                    {
                        arriba.vecinos.push_back(arriba.cX - 1);
                        arriba.vecinos.push_back(arriba.cY - 1);
                    }
                }
                //abajo derecha
                if ((arriba.cY + 1) < imgNueva.rows && (arriba.cY + 1) > 0 && (arriba.cX + 1) < imgNueva.rows && (arriba.cX + 1) > 0)
                {
                    if (verificacion(arriba.cX + 1, arriba.cY + 1))
                    {
                        arriba.vecinos.push_back(arriba.cX + 1);
                        arriba.vecinos.push_back(arriba.cY + 1);
                    }
                }
                //abajo izq
                if ((arriba.cY + 1) < imgNueva.rows && (arriba.cY + 1) > 0 && (arriba.cX - 1) < imgNueva.rows && (arriba.cX - 1) > 0)
                {
                    if (verificacion(arriba.cX - 1, arriba.cY + 1))
                    {
                        arriba.vecinos.push_back(arriba.cX - 1);
                        arriba.vecinos.push_back(arriba.cY + 1);
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
        if ((arregloHijos[i].cY + 1) < imgNueva.rows && (arregloHijos[i].cY + 1) > 0)
        {
            int intensidadPixel = (int)src_gray.at<uchar>(arregloHijos[i].cY + 1, arregloHijos[i].cX);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                Hijos abajo;
                abajo.cX = arregloHijos[i].cX;
                abajo.cY = arregloHijos[i].cY + 1;

                //abajo vecino
                if ((abajo.cY + 1) < imgNueva.rows && (abajo.cY + 1) > 0)
                {
                    if (verificacion(abajo.cX, abajo.cY + 1))
                    {
                        abajo.vecinos.push_back(abajo.cX);
                        abajo.vecinos.push_back(abajo.cY + 1);
                    }
                }
                //derecha vecino
                if ((abajo.cX + 1) < imgNueva.cols && (abajo.cX + 1) > 0)
                {
                    if (verificacion(abajo.cX + 1, abajo.cY))
                    {
                        abajo.vecinos.push_back(abajo.cX + 1);
                        abajo.vecinos.push_back(abajo.cY);
                    }
                }
                //izquierda vecino
                if ((abajo.cX + 1) < imgNueva.cols && (abajo.cX + 1) > 0)
                {
                    if (verificacion(abajo.cX - 1, abajo.cY))
                    {
                        abajo.vecinos.push_back(abajo.cX - 1);
                        abajo.vecinos.push_back(abajo.cY);
                    }
                }

                //diagonales

                //arriba derecha

                if ((abajo.cY - 1) < imgNueva.rows && (abajo.cY - 1) > 0 && (abajo.cX + 1) < imgNueva.rows && (abajo.cX + 1) > 0)
                {
                    if (verificacion(abajo.cX + 1, abajo.cY - 1))
                    {
                        abajo.vecinos.push_back(abajo.cX + 1);
                        abajo.vecinos.push_back(abajo.cY - 1);
                    }
                }
                //abajo izq
                if ((abajo.cY - 1) < imgNueva.rows && (abajo.cY - 1) > 0 && (abajo.cX - 1) < imgNueva.rows && (abajo.cX - 1) > 0)
                {
                    if (verificacion(abajo.cX - 1, abajo.cY - 1))
                    {
                        abajo.vecinos.push_back(abajo.cX - 1);
                        abajo.vecinos.push_back(abajo.cY - 1);
                    }
                }
                //abajo derecha
                if ((abajo.cY + 1) < imgNueva.rows && (abajo.cY + 1) > 0 && (abajo.cX + 1) < imgNueva.rows && (abajo.cX + 1) > 0)
                {
                    if (verificacion(abajo.cX + 1, abajo.cY + 1))
                    {
                        abajo.vecinos.push_back(abajo.cX + 1);
                        abajo.vecinos.push_back(abajo.cY + 1);
                    }
                }
                //abajo izq
                if ((abajo.cY + 1) < imgNueva.rows && (abajo.cY + 1) > 0 && (abajo.cX - 1) < imgNueva.rows && (abajo.cX - 1) > 0)
                {
                    if (verificacion(abajo.cX - 1, abajo.cY + 1))
                    {
                        abajo.vecinos.push_back(abajo.cX - 1);
                        abajo.vecinos.push_back(abajo.cY + 1);
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

        if ((arregloHijos[i].cX + 1) < imgNueva.cols && (arregloHijos[i].cX + 1) > 0)
        {
            int intensidadPixel = (int)src_gray.at<uchar>(arregloHijos[i].cY, arregloHijos[i].cX + 1);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                Hijos derecha;
                derecha.cX = arregloHijos[i].cX + 1;
                derecha.cY = arregloHijos[i].cY;

                //arriba vecino
                if ((derecha.cY - 1) < imgNueva.rows && (derecha.cY - 1) > 0)
                {
                    if (verificacion(derecha.cX, derecha.cY - 1))
                    {
                        derecha.vecinos.push_back(derecha.cX);
                        derecha.vecinos.push_back(derecha.cY - 1);
                    }
                }
                //abajo vecino
                if ((derecha.cY + 1) < imgNueva.rows && (derecha.cY + 1) > 0)
                {
                    if (verificacion(derecha.cX, derecha.cY + 1))
                    {
                        derecha.vecinos.push_back(derecha.cX);
                        derecha.vecinos.push_back(derecha.cY + 1);
                    }
                }
                //derecha vecino
                if ((derecha.cX + 1) < imgNueva.cols && (derecha.cX + 1) > 0)
                {
                    if (verificacion(derecha.cX + 1, derecha.cY))
                    {
                        derecha.vecinos.push_back(derecha.cX + 1);
                        derecha.vecinos.push_back(derecha.cY);
                    }
                }

                //diagonales

                //arriba derecha

                if ((derecha.cY - 1) < imgNueva.rows && (derecha.cY - 1) > 0 && (derecha.cX + 1) < imgNueva.rows && (derecha.cX + 1) > 0)
                {
                    if (verificacion(derecha.cX + 1, derecha.cY - 1))
                    {
                        derecha.vecinos.push_back(derecha.cX + 1);
                        derecha.vecinos.push_back(derecha.cY - 1);
                    }
                }
                //abajo izq
                if ((derecha.cY - 1) < imgNueva.rows && (derecha.cY - 1) > 0 && (derecha.cX - 1) < imgNueva.rows && (derecha.cX - 1) > 0)
                {
                    if (verificacion(derecha.cX - 1, derecha.cY - 1))
                    {
                        derecha.vecinos.push_back(derecha.cX - 1);
                        derecha.vecinos.push_back(derecha.cY - 1);
                    }
                }
                //abajo derecha
                if ((derecha.cY + 1) < imgNueva.rows && (derecha.cY + 1) > 0 && (derecha.cX + 1) < imgNueva.rows && (derecha.cX + 1) > 0)
                {
                    if (verificacion(derecha.cX + 1, derecha.cY + 1))
                    {
                        derecha.vecinos.push_back(derecha.cX + 1);
                        derecha.vecinos.push_back(derecha.cY + 1);
                    }
                }
                //abajo izq
                if ((derecha.cY + 1) < imgNueva.rows && (derecha.cY + 1) > 0 && (derecha.cX - 1) < imgNueva.rows && (derecha.cX - 1) > 0)
                {
                    if (verificacion(derecha.cX - 1, derecha.cY + 1))
                    {
                        derecha.vecinos.push_back(derecha.cX - 1);
                        derecha.vecinos.push_back(derecha.cY + 1);
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
        if ((arregloHijos[i].cX - 1) < imgNueva.cols && (arregloHijos[i].cX - 1) > 0)
        {
            int intensidadPixel = (int)src_gray.at<uchar>(arregloHijos[i].cY, arregloHijos[i].cX - 1);
            if (verificarIntensidad(intensidadOriginal + tolerancia, intensidadPixel, intensidadOriginal - tolerancia))
            {
                Hijos izquierda;
                izquierda.cX = arregloHijos[i].cX - 1;
                izquierda.cY = arregloHijos[i].cY;

                //arriba vecino
                if ((izquierda.cY - 1) < imgNueva.rows && (izquierda.cY - 1) > 0)
                {
                    if (verificacion(izquierda.cX, izquierda.cY - 1))
                    {
                        izquierda.vecinos.push_back(izquierda.cX);
                        izquierda.vecinos.push_back(izquierda.cY - 1);
                    }
                }
                //abajo vecino
                if ((izquierda.cY + 1) < imgNueva.rows && (izquierda.cY + 1) > 0)
                {
                    if (verificacion(izquierda.cX, izquierda.cY + 1))
                    {
                        izquierda.vecinos.push_back(izquierda.cX);
                        izquierda.vecinos.push_back(izquierda.cY + 1);
                    }
                }

                //izquierda vecino
                if ((izquierda.cX + 1) < imgNueva.cols && (izquierda.cX + 1) > 0)
                {
                    if (verificacion(izquierda.cX - 1, izquierda.cY))
                    {
                        izquierda.vecinos.push_back(izquierda.cX - 1);
                        izquierda.vecinos.push_back(izquierda.cY);
                    }
                }

                //diagonales

                //arriba derecha

                if ((izquierda.cY - 1) < imgNueva.rows && (izquierda.cY - 1) > 0 && (izquierda.cX + 1) < imgNueva.rows && (izquierda.cX + 1) > 0)
                {
                    if (verificacion(izquierda.cX + 1, izquierda.cY - 1))
                    {
                        izquierda.vecinos.push_back(izquierda.cX + 1);
                        izquierda.vecinos.push_back(izquierda.cY - 1);
                    }
                }
                //abajo izq
                if ((izquierda.cY - 1) < imgNueva.rows && (izquierda.cY - 1) > 0 && (izquierda.cX - 1) < imgNueva.rows && (izquierda.cX - 1) > 0)
                {
                    if (verificacion(izquierda.cX - 1, izquierda.cY - 1))
                    {
                        izquierda.vecinos.push_back(izquierda.cX - 1);
                        izquierda.vecinos.push_back(izquierda.cY - 1);
                    }
                }
                //abajo derecha
                if ((izquierda.cY + 1) < imgNueva.rows && (izquierda.cY + 1) > 0 && (izquierda.cX + 1) < imgNueva.rows && (izquierda.cX + 1) > 0)
                {
                    if (verificacion(izquierda.cX + 1, izquierda.cY + 1))
                    {
                        izquierda.vecinos.push_back(izquierda.cX + 1);
                        izquierda.vecinos.push_back(izquierda.cY + 1);
                    }
                }
                //abajo izq
                if ((izquierda.cY + 1) < imgNueva.rows && (izquierda.cY + 1) > 0 && (izquierda.cX - 1) < imgNueva.rows && (izquierda.cX - 1) > 0)
                {
                    if (verificacion(izquierda.cX - 1, izquierda.cY + 1))
                    {
                        izquierda.vecinos.push_back(izquierda.cX - 1);
                        izquierda.vecinos.push_back(izquierda.cY + 1);
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
