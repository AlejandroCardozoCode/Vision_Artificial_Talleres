#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    // Declare variables
    cv::Mat img1, img2, img3;
    
    img1 = cv::imread(argv[1], 1);
    if (img1.empty())
    {
        std::cout << "La imagen no se puedo abrir!\n"
                  << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }
    // Aplicar filtros
    for (int i = 0; i < 5; i++)
    {
        cv::medianBlur(img1, img2, 3);
    }
    cv::medianBlur(img1, img3, 11);

    //guardado de imagenes
    imwrite("resultado_3x3_medianBlur.jpg", img2);
    imwrite("resultado_11x11_medianBlur.jpg", img3);

    return 0;
}