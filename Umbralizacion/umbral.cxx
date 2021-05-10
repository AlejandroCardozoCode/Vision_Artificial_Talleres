
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using std::cout;

int main(int argc, char **argv)
{
    Mat src, src_gray, binaria, final, thres;
    int threshold_type = 0;
    int const max_binary_value = 255;

    src = imread(samples::findFile(argv[1]), 1); 
    if (src.empty())
    {
        cout << "Cannot read the image: " << std::endl;
        return -1;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY); 

    long double umbral = threshold(src_gray, thres, 0, 255, THRESH_BINARY + THRESH_OTSU);

    adaptiveThreshold(src_gray, final, umbral, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
    threshold(src_gray, binaria, umbral, max_binary_value, threshold_type);

    std::cout << "el umbral es de: " << umbral << std::endl;

    imwrite("Umbral.png", final);
    imwrite("Binaria.png", binaria);
    
    return 0;
}