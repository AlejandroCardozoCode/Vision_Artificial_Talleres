#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    // Declare variables
    cv::Mat img1, img2, img3;
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

    // inicializar variables
    anchor = cv::Point(-1, -1);
    delta = 0;
    ddepth = -1;
    kernel = cv::Mat::ones(3, 3, CV_32F) / (float)(3 * 3);
    // Aplicar filtros
    img2 = img1;
    for (int i = 0; i < 2; i++)
    {
        filter2D(img2, img2, ddepth, kernel, anchor, delta, cv::BORDER_DEFAULT);
    }
    cv::medianBlur(img2, img3, 3);
    //guardado de imagenes
    imwrite("resultado_final.jpg", img3);

    return 0;
}