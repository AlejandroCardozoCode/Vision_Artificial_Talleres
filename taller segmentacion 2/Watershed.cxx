#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
#include "itkWatershedImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkGradientMagnitudeImageFilter.h"


int main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cerr << "faltan parametros" << std::endl;
    std::cerr << "invocacion: " << argv[0] << " imagen threshold nivel" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dim = 2;

  using InputImageType = itk::Image<unsigned char, Dim>;
  using FloatImageType = itk::Image<float, Dim>;
  using RGBPixelType = itk::RGBPixel<unsigned char>;
  using RGBImageType = itk::Image<RGBPixelType, Dim>;
  using LabeledImageType = itk::Image<itk::IdentifierType, Dim>;

  using FileReaderType = itk::ImageFileReader<InputImageType>;
  FileReaderType::Pointer reader = FileReaderType::New();
  reader->SetFileName(argv[1]);

  using GradientMagnitudeImageFilterType = itk::GradientMagnitudeImageFilter<InputImageType, FloatImageType>;
  GradientMagnitudeImageFilterType::Pointer gradiente = GradientMagnitudeImageFilterType::New();

  gradiente->SetInput(reader->GetOutput());
  gradiente->Update();

  using WatershedFilterType = itk::WatershedImageFilter<FloatImageType>;
  WatershedFilterType::Pointer watershed = WatershedFilterType::New();

  float threshold = std::stod(argv[2]);
  float nivel = std::stod(argv[3]);

  watershed->SetThreshold(threshold);
  watershed->SetLevel(nivel);

  watershed->SetInput(gradiente->GetOutput());
  watershed->Update();

  using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
  RGBFilterType::Pointer filtoImageColor = RGBFilterType::New();
  filtoImageColor->SetColormap(itk::ScalarToRGBColormapImageFilterEnums::RGBColormapFilter::Jet);
  filtoImageColor->SetInput(watershed->GetOutput());
  filtoImageColor->Update();

  using FileWriterType = itk::ImageFileWriter<RGBImageType>;
  FileWriterType::Pointer writer = FileWriterType::New();
  writer->SetFileName("Watershed.png");
  writer->SetInput(filtoImageColor->GetOutput());
  writer->Update();

  return 0;
}