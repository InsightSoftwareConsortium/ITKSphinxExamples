#include "itkFastMarchingImageToNodePairContainerAdaptor.h"
#include "itkFastMarchingImageFilterBase.h"
#include "itkFastMarchingThresholdStoppingCriterion.h"
#include "itkImageFileWriter.h"

int main(int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << " <OutputFileName>" << std::endl;

    return EXIT_FAILURE;
    }

  // create a fastmarching object
  typedef float PixelType;
  const unsigned int Dimension = 2;

  typedef itk::Image< PixelType, Dimension > FloatImageType;

  typedef itk::FastMarchingThresholdStoppingCriterion< FloatImageType,
    FloatImageType > CriterionType;

  typedef itk::FastMarchingImageFilterBase< FloatImageType, FloatImageType >
    FastMarchingType;

  CriterionType::Pointer criterion = CriterionType::New();
  criterion->SetThreshold( 100. );

  FastMarchingType::Pointer marcher = FastMarchingType::New();
  marcher->SetStoppingCriterion( criterion );

  // specify the size of the output image
  FloatImageType::SizeType size = {{64,64}};
  marcher->SetOutputSize( size );

  // setup a speed image of ones
  FloatImageType::Pointer speedImage = FloatImageType::New();

  FloatImageType::RegionType region;
  region.SetSize( size );

  speedImage->SetLargestPossibleRegion( region );
  speedImage->SetBufferedRegion( region );
  speedImage->Allocate();
  speedImage->FillBuffer( 1.0 );

  // setup a 'alive image'
  FloatImageType::Pointer AliveImage = FloatImageType::New();
  AliveImage->SetLargestPossibleRegion( region );
  AliveImage->SetBufferedRegion( region );
  AliveImage->Allocate();
  AliveImage->FillBuffer( 0.0 );

  FloatImageType::OffsetType offset0 = {{28,35}};

  FloatImageType::IndexType index;
  index.Fill(0);
  index += offset0;

  AliveImage->SetPixel( index, 1.0 );

  // setup a 'trial image'
  FloatImageType::Pointer TrialImage = FloatImageType::New();
  TrialImage->SetLargestPossibleRegion( region );
  TrialImage->SetBufferedRegion( region );
  TrialImage->Allocate();
  TrialImage->FillBuffer( 0.0 );

  index[0] += 1;
  TrialImage->SetPixel( index, 1.0 );

  index[0] -= 1;
  index[1] += 1;
  TrialImage->SetPixel( index, 1.0 );

  index[0] -= 1;
  index[1] -= 1;
  TrialImage->SetPixel( index, 1.0 );

  index[0] += 1;
  index[1] -= 1;
  TrialImage->SetPixel( index, 1.0 );

  marcher->SetInput( speedImage );

  typedef itk::FastMarchingImageToNodePairContainerAdaptor< FloatImageType,
      FloatImageType, FloatImageType > AdaptorType;

  AdaptorType::Pointer adaptor = AdaptorType::New();

  adaptor->SetAliveImage( AliveImage.GetPointer() );
  adaptor->SetAliveValue( 0.0 );

  adaptor->SetTrialImage( TrialImage.GetPointer() );
  adaptor->SetTrialValue( 1.0 );
  adaptor->Update();

  marcher->SetAlivePoints( adaptor->GetAlivePoints() );
  marcher->SetTrialPoints( adaptor->GetTrialPoints() );

  typedef itk::ImageFileWriter< FloatImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( marcher->GetOutput() );
  writer->SetFileName( argv[1] );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
