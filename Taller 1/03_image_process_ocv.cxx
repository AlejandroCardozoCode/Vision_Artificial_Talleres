//Creado por Diego Alejadro Cardozo Rojas y Brayan Estiben Giraldo Lopez. En base al codigo enviado adtjunto al Taller 1

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
void modificarImagen (float tamanoNuevo, std ::string nombreImagen, std ::string nombreOriginal, int codigoColor);

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
  
  //Reducir
  modificarImagen(0.75, nombre + "_R.png", nombre, 0);
  modificarImagen(0.5, nombre + "_G.png", nombre, 1);
  modificarImagen(0.25, nombre + "_B.png", nombre, 2);

  //Reescalar
  modificarImagen(1.333333333, nombre + "_sR.png", nombre, 0 );
  modificarImagen(2, nombre + "_sG.png", nombre, 1 );
  modificarImagen(4, nombre + "_sB.png", nombre, 2 );

  // Recostruir las imagenes
  Mat imagenR, imagenG, imagenB;
  imagenR = imread( nombre + "_ssR.png" );
  imagenG = imread( nombre + "_ssG.png" );
  imagenB = imread( nombre + "_ssB.png" );

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

  imwrite( nombre + "_rRGB.png", canalRGB );

  //Comparar imagenes 
  Mat imagenNueva, comparacion;
  imagenNueva = imread( nombre + "_rRGB.png");

  subtract(Imagen_Ing, imagenNueva, comparacion);

  imwrite( nombre + "_diff.png", comparacion );

  return( 0 );
  
}

void modificarImagen (float tamanoNuevo, std ::string nombreImagen, std ::string nombreOriginal, int codigoColor){

  Mat imagenIngresada;
  imagenIngresada = imread(nombreImagen);
  
  Mat reescalado;
  resize(imagenIngresada, reescalado, Size(), tamanoNuevo, tamanoNuevo, INTER_LINEAR);

  switch (codigoColor)
  {
  case 0:
    if (tamanoNuevo < 1){
  imwrite( nombreOriginal + "_sR.png", reescalado );
  }
  else{
  imwrite( nombreOriginal + "_ssR.png", reescalado );
  }
    break;

  case 1:
  if (tamanoNuevo < 1){
  imwrite( nombreOriginal + "_sG.png", reescalado );
  }
  else{
  imwrite( nombreOriginal + "_ssG.png", reescalado );
  }
  break;

  case 2:
  if (tamanoNuevo < 1){
  imwrite( nombreOriginal + "_sB.png", reescalado );
  }
  else{
  imwrite( nombreOriginal + "_ssB.png", reescalado );
  }
  break;

  default:
    break;
  }
}

