//Creado por Diego Alejadro Cardozo Rojas y Brayan Estiben Giraldo Lopez. En base al codigo enviado adtjunto al Taller 1

#include <cmath>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <string>
#include <sstream>

#include <itkImage.h>
#include <itkRGBPixel.h>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkImageRegionConstIteratorWithIndex.h>
#include <itkImageRegionIteratorWithIndex.h>

#include <itkIdentityTransform.h>
#include <itkResampleImageFilter.h>

#include "itkSubtractImageFilter.h"


// Image type: 2-dimensional 1-byte rgb
const unsigned int Dim = 2;
typedef unsigned char TRGBResolution;
typedef itk::RGBPixel<TRGBResolution> TRGBPixel;
typedef itk::Image<TRGBPixel, Dim> TColorImage;

// Types definition
typedef itk::ImageFileReader<TColorImage> TReader;
typedef itk::ImageRegionConstIteratorWithIndex<TColorImage> TIterator;
typedef itk::ImageRegionIteratorWithIndex<TColorImage> TColorIterator;
typedef itk::ImageFileWriter<TColorImage> TWriter;
typedef itk::IdentityTransform<double, 2> TransformType;
typedef itk::ResampleImageFilter<TColorImage, TColorImage> ResampleImageFilterType;
typedef itk::ImageFileWriter<TColorImage> TWriter;

void reescalado(float tamano, std::string nombreImagen, std::string final, int modoUso)
{
    TReader::Pointer reader = TReader::New();
    TColorImage *imgen_nueva;
    TColorImage::SizeType tamanoInicialRojo;
    TColorImage::SizeType tamanoFinalRojo;

    if (modoUso == 0)
    {
        std::string nombreCompleto = nombreImagen + "_" + final + ".png";
        reader->SetFileName(nombreCompleto);
        try
        {
            reader->Update();
        }
        catch (itk::ExceptionObject &err)
        {
            std::cerr << "Error: " << err << std::endl;
            return;

        }  

        imgen_nueva = reader->GetOutput();
        tamanoInicialRojo = imgen_nueva->GetLargestPossibleRegion().GetSize();
        tamanoFinalRojo[0] = tamanoInicialRojo[0] * tamano;
        tamanoFinalRojo[1] = tamanoInicialRojo[1] * tamano;
    }

    if (modoUso == 1)
    {
        std::string nombreCompleto = nombreImagen + "_s" + final + ".png";
        reader->SetFileName(nombreCompleto);
        try
        {
            reader->Update();
        }
        catch (itk::ExceptionObject &err)
        {
            std::cerr << "Error: " << err << std::endl;
            return;

        }  

        imgen_nueva = reader->GetOutput();
        tamanoInicialRojo = imgen_nueva->GetLargestPossibleRegion().GetSize();
        tamanoFinalRojo[0] = tamanoInicialRojo[0] / tamano;
        tamanoFinalRojo[1] = tamanoInicialRojo[1] / tamano;
    }

    //calcular espaciadoRojo

    TColorImage::SpacingType espaciadoRojo;
    espaciadoRojo[0] =
        imgen_nueva->GetSpacing()[0] * (static_cast<double>(tamanoInicialRojo[0]) / static_cast<double>(tamanoFinalRojo[0]));
    espaciadoRojo[1] =
        imgen_nueva->GetSpacing()[1] * (static_cast<double>(tamanoInicialRojo[1]) / static_cast<double>(tamanoFinalRojo[1]));

    // Rescale image
    ResampleImageFilterType::Pointer resampleFilter = ResampleImageFilterType::New();
    resampleFilter->SetTransform(TransformType::New());
    resampleFilter->SetInput(imgen_nueva);
    resampleFilter->SetSize(tamanoFinalRojo);
    resampleFilter->SetOutputSpacing(espaciadoRojo);
    resampleFilter->UpdateLargestPossibleRegion();

    if (modoUso == 0)
    {
        TWriter::Pointer writer = TWriter::New();
        writer->SetInput(resampleFilter->GetOutput());
        writer->SetFileName(nombreImagen + "_s" + final + ".png");
        try
        {
            writer->Update();
        }
        catch (itk::ExceptionObject &err)
        {
            std::cerr << "Error: " << err << std::endl;
            return;

        }
    }

    if (modoUso == 1)
    {
        TWriter::Pointer writer = TWriter::New();
        writer->SetInput(resampleFilter->GetOutput());
        writer->SetFileName(nombreImagen + "_ss" + final + ".png");
        try
        {
            writer->Update();
        }
        catch (itk::ExceptionObject &err)
        {
            std::cerr << "Error: " << err << std::endl;
            return;

        }  
    }

    return;
}

int main(int argc, char *argv[])
{

    std::cout << "-------------------------" << std::endl;
    for (int a = 0; a < argc; a++)
        std::cout << argv[a] << std::endl;
    std::cout << "-------------------------" << std::endl;

    // Read an image
    TReader::Pointer reader = TReader::New();
    reader->SetFileName(argv[1]);
    try
    {
        reader->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  
    TColorImage *imagen_original = reader->GetOutput();

    // creacion de los canales de colores rojo, verde, azul y llenado de color negro 

    TColorImage::Pointer canalRojo = TColorImage::New();
    canalRojo->SetSpacing(imagen_original->GetSpacing());
    canalRojo->SetOrigin(imagen_original->GetOrigin());
    canalRojo->SetLargestPossibleRegion(imagen_original->GetLargestPossibleRegion());
    canalRojo->SetRequestedRegion(imagen_original->GetRequestedRegion());
    canalRojo->SetBufferedRegion(imagen_original->GetBufferedRegion());
    canalRojo->Allocate();

    TColorImage::Pointer canalVerde = TColorImage::New();
    canalVerde->SetSpacing(imagen_original->GetSpacing());
    canalVerde->SetOrigin(imagen_original->GetOrigin());
    canalVerde->SetLargestPossibleRegion(imagen_original->GetLargestPossibleRegion());
    canalVerde->SetRequestedRegion(imagen_original->GetRequestedRegion());
    canalVerde->SetBufferedRegion(imagen_original->GetBufferedRegion());
    canalVerde->Allocate();

    TColorImage::Pointer canalAzul = TColorImage::New();
    canalAzul->SetSpacing(imagen_original->GetSpacing());
    canalAzul->SetOrigin(imagen_original->GetOrigin());
    canalAzul->SetLargestPossibleRegion(imagen_original->GetLargestPossibleRegion());
    canalAzul->SetRequestedRegion(imagen_original->GetRequestedRegion());
    canalAzul->SetBufferedRegion(imagen_original->GetBufferedRegion());
    canalAzul->Allocate();

    TRGBPixel canalNegro;
    canalNegro.SetRed(0);
    canalNegro.SetGreen(0);
    canalNegro.SetBlue(0);
    canalRojo->FillBuffer(canalNegro);
    canalVerde->FillBuffer(canalNegro);
    canalAzul->FillBuffer(canalNegro);

    TIterator iteradorOriginal(imagen_original, imagen_original->GetLargestPossibleRegion());
    TColorIterator iteradorRojo(canalRojo, canalRojo->GetLargestPossibleRegion());
    TColorIterator iteradorVerde(canalVerde, canalVerde->GetLargestPossibleRegion());
    TColorIterator iteradorAzul(canalAzul, canalAzul->GetLargestPossibleRegion());

    //inicio de los iteradores

    iteradorOriginal.GoToBegin();
    iteradorRojo.GoToBegin();
    iteradorVerde.GoToBegin();
    iteradorAzul.GoToBegin();

    //llenado de los canales con su respectivo colo r

    for (; !iteradorOriginal.IsAtEnd() && !iteradorRojo.IsAtEnd() && !iteradorVerde.IsAtEnd() && !iteradorAzul.IsAtEnd(); ++iteradorOriginal, ++iteradorRojo, ++iteradorVerde, ++iteradorAzul)
    {
        TRGBPixel value, pixel;
        pixel = iteradorOriginal.Get();
        value.SetRed(pixel.GetRed());
        value.SetGreen(0);
        value.SetBlue(0);
        iteradorRojo.Set(value);

        value.SetRed(0);
        value.SetGreen(pixel.GetGreen());
        value.SetBlue(0);
        iteradorVerde.Set(value);

        value.SetRed(0);
        value.SetGreen(0);
        value.SetBlue(pixel.GetBlue());
        iteradorAzul.Set(value);
    }

    // creacion de la imagen roja

    std::stringstream parametros(argv[1]);
    std::string  nombreArchivo;
    getline(parametros,  nombreArchivo, '.');

    TWriter::Pointer writer = TWriter::New();
    writer->SetInput(canalRojo);
    writer->SetFileName( nombreArchivo + "_R.png");
    try
    {
        writer->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  

    // creacion de la imagen Verde

    writer->SetInput(canalVerde);
    writer->SetFileName( nombreArchivo + "_G.png");
    try
    {
        writer->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  

    // creacion de la Azul

    writer->SetInput(canalAzul);
    writer->SetFileName( nombreArchivo + "_B.png");
    try
    {
        writer->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  

    //funciones para hacer las imagenes mas pequeños 

    reescalado(0.75,  nombreArchivo, "R", 0);
    reescalado(0.5,  nombreArchivo, "G", 0);
    reescalado(0.25,  nombreArchivo, "B", 0);

    //funciones para restaurar el tamaño de las imagenes

    reescalado(0.75,  nombreArchivo, "R", 1);
    reescalado(0.5,  nombreArchivo, "G", 1);
    reescalado(0.25,  nombreArchivo, "B", 1);

    //reconstruccion de la imagen

    TReader::Pointer readerRojo = TReader::New();
    readerRojo->SetFileName( nombreArchivo + "_ssR.png");
    try
    {
        readerRojo->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  

    TColorImage *escaladaRoja = readerRojo->GetOutput();

    TReader::Pointer readerVerde = TReader::New();
    readerVerde->SetFileName( nombreArchivo + "_ssG.png");
    try
    {
        readerVerde->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  

    TColorImage *escaladaVerde = readerVerde->GetOutput();

    TReader::Pointer readerAzul = TReader::New();
    readerAzul->SetFileName( nombreArchivo + "_ssB.png");
    try
    {
        readerAzul->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  

    TColorImage *escaladaAzul = readerAzul->GetOutput();

    //creacion de canales de la imgen final

    TColorImage::Pointer imagenFinal = TColorImage::New();
    imagenFinal->SetSpacing(imagen_original->GetSpacing());
    imagenFinal->SetOrigin(imagen_original->GetOrigin());
    imagenFinal->SetLargestPossibleRegion(imagen_original->GetLargestPossibleRegion());
    imagenFinal->SetRequestedRegion(imagen_original->GetRequestedRegion());
    imagenFinal->SetBufferedRegion(imagen_original->GetBufferedRegion());
    imagenFinal->Allocate();


    // creaion de los iteradores de las imagenes finales

    TColorIterator iteradorImagenFinal(imagenFinal, imagenFinal->GetLargestPossibleRegion());
    TColorIterator iteradorFinalRojo(escaladaRoja, escaladaRoja->GetLargestPossibleRegion());
    TColorIterator iteradorFinalVerde(escaladaVerde, escaladaVerde->GetLargestPossibleRegion());
    TColorIterator iteradorFinalAzul(escaladaAzul, escaladaAzul->GetLargestPossibleRegion());

    iteradorImagenFinal.GoToBegin();
    iteradorFinalRojo.GoToBegin();
    iteradorFinalVerde.GoToBegin();
    iteradorFinalAzul.GoToBegin();

    //reconstruccion de la imagen final

    for (; !iteradorImagenFinal.IsAtEnd() && !iteradorFinalRojo.IsAtEnd() && !iteradorFinalVerde.IsAtEnd() && !iteradorFinalAzul.IsAtEnd(); ++iteradorImagenFinal, ++iteradorFinalRojo, ++iteradorFinalVerde, ++iteradorFinalAzul)
    {
        TRGBPixel value, pixel;
        value = iteradorFinalRojo.Get();
        pixel.SetRed(value.GetRed());

        value = iteradorFinalVerde.Get();
        pixel.SetGreen(value.GetGreen());

        value = iteradorFinalAzul.Get();
        pixel.SetBlue(value.GetBlue());

        iteradorImagenFinal.Set(pixel);
    }

    //guardado de la imagen final

    writer->SetInput(imagenFinal);
    writer->SetFileName( nombreArchivo + "_rRGB.png");
    try
    {
        writer->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  

    //comparacion de la imagen original y la procesada

    TColorImage * resultado = TColorImage::New();
    using SubtractImageFilterType = itk::SubtractImageFilter<TColorImage, TColorImage>;
    SubtractImageFilterType::Pointer subtractFilter = SubtractImageFilterType::New();
    subtractFilter->SetInput1(imagenFinal);
    subtractFilter->SetInput2(imagen_original);
    subtractFilter->Update();

    //guardado de la diferencia

    writer->SetInput(subtractFilter->GetOutput());
    writer->SetFileName( nombreArchivo + "_diff.png");
    try
    {
        writer->Update();
    }
    catch (itk::ExceptionObject &err)
    {
        std::cerr << "Error: " << err << std::endl;
        return (1);

    }  

    return (0);
}