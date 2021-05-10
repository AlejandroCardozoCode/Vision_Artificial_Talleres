#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkConfidenceConnectedImageFilter.h"
#include "itkImageFileWriter.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

using ImageType = itk::Image<unsigned char, 2>;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "invocacion: imagen.png valorX ValorY" << std::endl;

        return EXIT_FAILURE;
    }
    std::string nombreArchivo = argv[1];

    using ReaderType = itk::ImageFileReader<ImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(nombreArchivo.c_str());
    reader->Update();

    using ConfidenceConnectedFilterType = itk::ConfidenceConnectedImageFilter<ImageType, ImageType>;
    ConfidenceConnectedFilterType::Pointer confidenceConnectedFilter = ConfidenceConnectedFilterType::New();
    confidenceConnectedFilter->SetInitialNeighborhoodRadius(3);
    confidenceConnectedFilter->SetMultiplier(3);
    confidenceConnectedFilter->SetNumberOfIterations(25);
    confidenceConnectedFilter->SetReplaceValue(255);

    ImageType::IndexType valor;
    valor[0] = std::stoi(argv[2]);
    valor[1] = std::stoi(argv[3]);
    confidenceConnectedFilter->SetSeed(valor);
    confidenceConnectedFilter->SetInput(reader->GetOutput());

    using FileWriterType = itk::ImageFileWriter<ImageType>;
    FileWriterType::Pointer writer = FileWriterType::New();
    writer->SetFileName("Pixels.png");
    writer->SetInput(confidenceConnectedFilter->GetOutput());
    writer->Update();

    return 0;
}