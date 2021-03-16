#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    // Declare variables
    cv::Mat img1;
    cv::Mat kernel;
    cv::Point anchor;
    double delta;
    int ddepth;

    img1 = cv::imread(argv[1], 1);
    if (img1.empty())
    {
        std::cout << "La imagen no se puedo abrir!\n"
                  << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }

    cv::Mat imagenReducida, imagenAux;
    cv::Size size(img1.cols / 2, img1.rows / 2);
    imagenReducida = cv::Mat::zeros(size, CV_8UC1);
    std::cout << "las filas de la imagen reducida son: " << imagenReducida.rows << std::endl;
    std::cout << "las columnas de la imagen reducida son: " << imagenReducida.cols << std::endl;
    cv::medianBlur(img1, imagenAux, 3);
    for (int i = 0; i < imagenReducida.rows; i++)
    {
        for (int j = 0; j < imagenReducida.cols; j++)
        {
            std::cout << "se esta modificando el pixel " << i << j << std::endl;
            imagenReducida.at<uchar>(i, j) = imagenAux.at<uchar>(i * 2, j * 6);
        }
    }
    imwrite("final.png", imagenReducida);
}