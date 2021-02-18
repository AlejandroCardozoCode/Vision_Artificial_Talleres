#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
    Mat src = imread( "ricardo.jpg",1  );
    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    
    Point2f srcTri[3];
    srcTri[0] = Point2f( 0.f, 0.f );
    srcTri[1] = Point2f( src.cols - 1.f, 0.f );
    srcTri[2] = Point2f( 0.f, src.rows - 1.f );
    Point2f dstTri[3];
    dstTri[0] = Point2f( 0.f, src.rows*0.33f );
    dstTri[1] = Point2f( src.cols*0.85f, src.rows*0.25f );
    dstTri[2] = Point2f( src.cols*0.15f, src.rows*0.7f );

    Mat warp_dst = Mat::zeros( src.rows, src.cols, src.type() );
    
    //warpAffine( src, warp_dst, warp_mat, warp_dst.size() );
    
    Point center = Point( (warp_dst.cols/2) , (warp_dst.rows/2));
    double angle = -35;
    double scale = 0.8;
    Mat rot_mat = getRotationMatrix2D( center, angle, scale );
    Mat warp_rotate_dst, trans;
    
    warpAffine( src, warp_rotate_dst, rot_mat, src.size() );
    

    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, -42, 0, 1, 37);
    warpAffine( warp_rotate_dst, trans, trans_mat, src.size());
    
    imwrite( "Source image.jpg", src );
    imwrite( "Warp + Rotate.jpg", warp_rotate_dst );
    imwrite( "Warp + affafafaf.jpg", trans );
    
    return 0;
}