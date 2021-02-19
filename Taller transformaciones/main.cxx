#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

void funcio2(){}

void metodoFunciones ( Mat img1){

    Mat img2, img3, final;
    resize(img1, img2, Size(), 0.8, 0.8);
    Point2f punto(img2.cols/2., img2.rows/2.); 
    Mat M = getRotationMatrix2D(punto, -35, 1);
    warpAffine(img2, img3, M, Size(img2.cols, img2.rows));
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, -42, 0, 1, 37);
    warpAffine( img3, final, trans_mat, img1.size());
    imwrite("final_metodo_funciones.jpg", final);
    return;
}

void metodo2Matriz ( Mat img1){

    Mat img2, img3, final;

    Point2f srcTri[3];
    srcTri[0] = Point2f( 0.f, 0.f );
    srcTri[1] = Point2f( img1.cols - 1.f, 0.f );
    srcTri[2] = Point2f( 0.f, img1.rows - 1.f );
    Point2f dstTri[3];
    dstTri[0] = Point2f( 0.f, img1.rows*0.33f );
    dstTri[1] = Point2f( img1.cols*0.85f, img1.rows*0.25f );
    dstTri[2] = Point2f( img1.cols*0.15f, img1.rows*0.7f );

    Mat warp_dst = Mat::zeros( img1.rows, img1.cols, img1.type() );

    Point centro = Point( (warp_dst.cols/2) , (warp_dst.rows/2));
    double angulo = -35;
    double rescalado = 0.8;
    Mat matrizRotacion = getRotationMatrix2D( centro, angulo, rescalado );

    warpAffine( img1, img2, matrizRotacion, img1.size() );
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, -42, 0, 1, 37);
    warpAffine( img2, img3, trans_mat, img1.size());

    imwrite( "final_metodo_matriz.jpg", img3 );
    return;
}
int main(int argc, char **argv)
{
    Mat img1 = imread(argv[1], 1), img2, img3, final;
    if (img1.empty())
    {
        cout << "Could not open or find the image!\n"
             << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    metodoFunciones(img1);
    metodo2Matriz(img1);
 
    return 0;
}