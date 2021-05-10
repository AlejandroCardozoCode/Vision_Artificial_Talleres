
/*----------------------------------------------------------------
taller de morfologia matematica programado por alejandro cardozo y brayan giraldo basado en los codigos
dados por la profesora en el taller de
*/

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int erosion_size = 3;
int dilation_size = 3;

Mat erosionfuncion(Mat src_gray)
{
  Mat erosion_dst, element = getStructuringElement(MORPH_RECT,Size(2 * erosion_size + 1, 2 * erosion_size + 1),Point(erosion_size, erosion_size));
  erode(src_gray, erosion_dst, element);
  imwrite("erosion.png", erosion_dst);
  return erosion_dst;
}

Mat dilatacionfuncion(Mat src_gray)
{
  Mat dilation_dst, element = getStructuringElement(MORPH_RECT,Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
  dilate(src_gray, dilation_dst, element);
  return dilation_dst;
}

Mat aperturafuncion(Mat src_gray)
{
  Mat erosion, dilatacion;

  erosion = erosionfuncion(src_gray);
  dilatacion = dilatacionfuncion(erosion);

  return dilatacion;
}

Mat cierrefuncion(Mat src_gray)
{
  Mat erosion, dilatacion;
  dilatacion = dilatacionfuncion(src_gray);
  erosion = erosionfuncion(dilatacion);

  return erosion;
}

int main(int argc, char *argv[])
{
  Mat src, src_gray, gradiente, erosion, dilatacion, apertura, cierre, topHat, bottonHat;
  src = imread(argv[1], 1);
  if (src.empty())
  {
    cout << "Could not open or find the image!\n"
         << endl;
    cout << "Usage: " << argv[0] << " <Input image>" << endl;
    return -1;
  }
  cvtColor(src, src_gray, COLOR_BGR2GRAY);
  int erosion_size = 3;
  int dilation_size = 3;
  erosion = erosionfuncion(src_gray);
  dilatacion = dilatacionfuncion(src_gray);

  cierre = cierrefuncion(src_gray);
  apertura = aperturafuncion(src_gray);

  subtract(src_gray,apertura, topHat);
  subtract(cierre, src_gray, bottonHat);
  subtract(dilatacion, erosion, gradiente);


  imwrite("top-hat.png", topHat);
  imwrite("botton-hat.png", bottonHat);
  imwrite("gradiente.png", gradiente);
  return 0;
}
