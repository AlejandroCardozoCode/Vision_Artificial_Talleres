#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void cuantificacion (std::string nombre, std::string tipo, int numero_bits )
{
  
  // Convert RGB image to grayscale
  Mat imagen_color;
  imagen_color = imread(nombre +  tipo + ".png", 1);

  // Quantize into desired number of bits
  uchar table[ 256 ];
  int scale = pow( 2, 8 - numero_bits );
  for (int i = 0; i < 256; ++i)
    table[ i ] = ( uchar )( scale * ( i / scale ) );

  Mat resint_img = Mat::zeros( imagen_color.size( ), CV_8UC1 );
  MatIterator_< uchar > it, end;
  for( it = resint_img.begin< uchar >( ), end = resint_img.end< uchar >( ); it != end; ++it)
    *it = table[*it];

  // Rescale intensities to cover the full range
  Mat lookUpTable(1, 256, CV_8U);
  uchar* p = lookUpTable.data;
  for( int i = 0; i < 256; ++i)
    p[i] = table[i];
  LUT(imagen_color, lookUpTable, resint_img);

  // Write results
  imwrite( nombre + tipo + "_rescaleInt.png", resint_img );

}

int main(int argc, char** argv )
{
  Mat Imagen_Ing;
  Imagen_Ing = imread( argv[1], 1 );

  if ( !Imagen_Ing.data )
  {
    std::cerr << "Error: No hay informacion de la imagen" << std::endl;
    return( -1);
  
  }

  //Crea loa canales
  Mat canalRojo = Mat::zeros( Imagen_Ing.size( ), CV_8UC3 );
  Mat canalVerde = Mat::zeros( Imagen_Ing.size( ), CV_8UC3 );
  Mat canalAzul = Mat::zeros( Imagen_Ing.size( ), CV_8UC3 );
 
  //Inicializa los oteradores
  MatIterator_< Vec3b > iteracion, iteRojo, iteVerde, iteAzul, fin, finRojo, finVerde, finAzul;

  //Division de las imagenes en R, G, B
  iteracion = Imagen_Ing.begin< Vec3b >( );
  iteRojo = canalRojo.begin< Vec3b >( );
  iteVerde = canalVerde.begin< Vec3b >( );
  iteAzul = canalAzul.begin< Vec3b >( );
  fin = Imagen_Ing.end< Vec3b >( );
  finRojo = canalRojo.end< Vec3b >( );
  finVerde = canalVerde.end< Vec3b >( );
  finAzul = canalAzul.end< Vec3b >( );
  for(  ; iteracion != fin, iteRojo != finRojo, iteVerde != finVerde, iteAzul != finAzul; ++iteracion, ++iteRojo, ++iteVerde, ++iteAzul)
  {
  	(*iteRojo)[0] = 0;
  	(*iteRojo)[1] = 0;
  	(*iteRojo)[2] = (*iteracion)[2];

  	(*iteVerde)[0] = 0;
  	(*iteVerde)[1] = (*iteracion)[1];
  	(*iteVerde)[2] = 0;
  	
  	(*iteAzul)[0] = (*iteracion)[0];
  	(*iteAzul)[1] = 0;
  	(*iteAzul)[2] = 0;

  } 
  
  std::stringstream sec( argv[ 1 ] );
  std::string nombre;
  getline( sec, nombre, '.' );

  //Guardo de las imagenes
  imwrite( nombre + "_R.png", canalRojo );
  imwrite( nombre + "_G.png", canalVerde );
  imwrite( nombre + "_B.png", canalAzul );

  int cantidadBits = atoi(argv[2]);

  cuantificacion(nombre, "_R", cantidadBits);
  cuantificacion(nombre, "_G", cantidadBits);
  cuantificacion(nombre, "_B", cantidadBits);


 // Recostruir las imagenes
  Mat imagenR, imagenG, imagenB;
  imagenR = imread( nombre + "_R_rescaleInt.png" );
  imagenG = imread( nombre + "_G_rescaleInt.png" );
  imagenB = imread( nombre + "_B_rescaleInt.png" );

  Mat canalRGB = Mat::zeros( Imagen_Ing.size( ), CV_8UC3 );
  MatIterator_< Vec3b > iteRojoNue, iteVerdeNue, iteAzulNue, iteRGB, finRojoNue, finVerdeNue, finAzulNue, finRGB;

  iteRojoNue = imagenR.begin< Vec3b >( );
  iteVerdeNue = imagenG.begin< Vec3b >( );
  iteAzulNue = imagenB.begin< Vec3b >( );
  iteRGB = canalRGB.begin< Vec3b >( );
  finRojoNue = imagenR.end< Vec3b >( );
  finVerdeNue = imagenG.end< Vec3b >( );
  finAzulNue = imagenB.end< Vec3b >( );
  finRGB = canalRGB.end< Vec3b >( );
  for(  ; iteRojoNue != finRojoNue, iteVerdeNue != finVerdeNue, iteAzulNue != finAzulNue, iteRGB != finRGB; ++iteRojoNue, ++iteVerdeNue, ++iteAzulNue, ++iteRGB)
  {
  	(*iteRGB)[0] = (*iteAzulNue)[0];
  	(*iteRGB)[1] = (*iteVerdeNue)[1];
  	(*iteRGB)[2] = (*iteRojoNue)[2];
  } 

  imwrite( nombre + "_rRGB_rescaleInt.png", canalRGB );

  return(0);


}



// eof - 02_rescale_intensity.cxx
