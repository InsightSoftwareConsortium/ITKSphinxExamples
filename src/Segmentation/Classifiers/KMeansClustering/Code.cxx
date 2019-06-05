/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkScalarImageKmeansImageFilter.h>

int main( int argc, char * argv [] )
{
  //sample usage
  //./kMeansClustering input.jpg output.jpg 1 3 0 100 200

  //verify command line arguments
  if( argc < 5 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " inputScalarImage outputLabeledImage contiguousLabels";
    std::cerr << " numberOfClasses mean1 mean2... meanN " << std::endl;
    return EXIT_FAILURE;
    }

  //parse command line arguments
  const char * inputImageFileName = argv[1];
  const char * outputImageFileName = argv[2];
  const unsigned int useNonContiguousLabels = std::stoi( argv[3] );
  const unsigned int numberOfInitialClasses = std::stoi( argv[4] );

  constexpr unsigned int argoffset = 5;

  if( static_cast<unsigned int>(argc) <
      numberOfInitialClasses + argoffset )
    {
    std::cerr << "Error: " << std::endl;
    std::cerr << numberOfInitialClasses << " classes has been specified ";
    std::cerr << "but no enough means have been provided in the command ";
    std::cerr << "line arguments " << std::endl;
    return EXIT_FAILURE;
    }

  std::vector<double> userMeans;
  for( unsigned k = 0; k < numberOfInitialClasses; k++ )
    {
    const double userProvidedInitialMean = std::stod( argv[k+argoffset] );
    userMeans.push_back(userProvidedInitialMean);
    }

  // Define the pixel type and dimension of the image that we intend to
  // classify.

  using PixelType = signed short;
  constexpr unsigned int Dimension = 2;

  using ImageType = itk::Image<PixelType, Dimension >;

  // create a reader
  using ReaderType = itk::ImageFileReader< ImageType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputImageFileName );

  // Instantiate the ScalarImageKmeansImageFilter
  using KMeansFilterType = itk::ScalarImageKmeansImageFilter< ImageType >;

  KMeansFilterType::Pointer kmeansFilter = KMeansFilterType::New();

  kmeansFilter->SetInput( reader->GetOutput() );

  // Make the output image intellegable by expanding the range of output image values, if desired

  kmeansFilter->SetUseNonContiguousLabels( useNonContiguousLabels );

  // initialize using the user input means

    for( unsigned k = 0; k < numberOfInitialClasses; k++ )
    {
    kmeansFilter->AddClassWithInitialMean( userMeans[k] );
    }

  // Create and setup a writer

  using OutputImageType = KMeansFilterType::OutputImageType;

  using WriterType = itk::ImageFileWriter< OutputImageType >;

  WriterType::Pointer writer = WriterType::New();

  writer->SetInput( kmeansFilter->GetOutput() );

  writer->SetFileName( outputImageFileName );

  // execut the pipeline
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Problem encountered while writing ";
    std::cerr << " image file : " << outputImageFileName << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  // inspect the means
  KMeansFilterType::ParametersType estimatedMeans =
                                            kmeansFilter->GetFinalMeans();

  const unsigned int numberOfClasses = estimatedMeans.Size();

  for ( unsigned int i = 0; i < numberOfClasses; ++i )
    {
    std::cout << "cluster[" << i << "] ";
    std::cout << "    estimated mean : " << estimatedMeans[i] << std::endl;
    }

  return EXIT_SUCCESS;

}

