#include <iostream>

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
#include "itkVectorMagnitudeImageFilter.h"
#include "itkMorphologicalWatershedImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkGradientMagnitudeImageFilter.h"

using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;
using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;
using LabeledImageType = itk::Image<unsigned long, 2>;

static void CreateImage(UnsignedCharImageType::Pointer image);
static void segmentar(FloatImageType::Pointer image, const float threshold, const float level);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "faltan parametros" << std::endl;
        std::cerr << "invocacion: " << argv[0] << " imagen threshold nivel" << std::endl;
        return 1;
    }

    std::string strThreshold = argv[1];
    float threshold = 0.0;
    std::stringstream ssThreshold;
    ssThreshold << strThreshold;
    ssThreshold >> threshold;

    std::string strLevel = argv[2];
    float level = 0.0;
    std::stringstream ssLevel;
    ssLevel << strLevel;
    ssLevel >> level;

    using InputImageType = itk::Image<unsigned char, 2>;

    using FileReaderType = itk::ImageFileReader<InputImageType>;
    FileReaderType::Pointer reader = FileReaderType::New();
    reader->SetFileName(argv[1]);

    using GradientMagnitudeImageFilterType = itk::GradientMagnitudeImageFilter<UnsignedCharImageType, FloatImageType>;
    GradientMagnitudeImageFilterType::Pointer gradiente = GradientMagnitudeImageFilterType::New();

    gradiente->SetInput(reader->GetOutput());
    gradiente->Update();

    segmentar(gradiente->GetOutput(), threshold, level);

    return 0;
}

void segmentar(FloatImageType::Pointer image, const float threshold, const float level)
{
    using MorphologicalWatershedFilterType = itk::MorphologicalWatershedImageFilter<FloatImageType, LabeledImageType>;
    MorphologicalWatershedFilterType::Pointer watershedFilter = MorphologicalWatershedFilterType::New();
    watershedFilter->SetLevel(level);
    watershedFilter->SetInput(image);
    watershedFilter->Update();

    using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
    RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
    colormapImageFilter->SetInput(watershedFilter->GetOutput());
    colormapImageFilter->SetColormap(itk::ScalarToRGBColormapImageFilterEnums::RGBColormapFilter::Jet);
    colormapImageFilter->Update();

    using FileWriterType = itk::ImageFileWriter<RGBImageType>;
    FileWriterType::Pointer writer = FileWriterType::New();
    writer->SetFileName("Morphological_Watershed.png");
    writer->SetInput(colormapImageFilter->GetOutput());
    writer->Update();
}