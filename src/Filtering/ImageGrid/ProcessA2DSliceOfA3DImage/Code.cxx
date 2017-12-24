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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkExtractImageFilter.h"
#include "itkPasteImageFilter.h"
#include "itkMedianImageFilter.h"

int main( int argc, char ** argv )
{
  // Verify the number of parameters in the command line
  if( argc <= 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " input3DImageFile  output3DImageFile " << std::endl;
    std::cerr << " sliceNumber " << std::endl;
    return EXIT_FAILURE;
    }

  typedef short PixelType;

  typedef itk::Image< PixelType, 3 > ImageType;

  typedef itk::ImageFileReader< ImageType > ReaderType;
  typedef itk::ImageFileWriter< ImageType > WriterType;

  // Here we recover the file names from the command line arguments
  const char * inputFilename  = argv[1];
  const char * outputFilename = argv[2];

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFilename  );
  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }

  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFilename );

  typedef itk::ExtractImageFilter< ImageType, ImageType >
    ExtractFilterType;
  ExtractFilterType::Pointer extractFilter = ExtractFilterType::New();
  extractFilter->SetDirectionCollapseToSubmatrix();

  // set up the extraction region [one slice]
  const ImageType * inputImage = reader->GetOutput();
  ImageType::RegionType inputRegion = inputImage->GetBufferedRegion();
  ImageType::SizeType size = inputRegion.GetSize();
  size[2] = 1; // we extract along z direction
  ImageType::IndexType start = inputRegion.GetIndex();
  const unsigned int sliceNumber = atoi( argv[3] );
  start[2] = sliceNumber;
  ImageType::RegionType desiredRegion;
  desiredRegion.SetSize(  size  );
  desiredRegion.SetIndex( start );

  extractFilter->SetExtractionRegion( desiredRegion );
  typedef itk::PasteImageFilter< ImageType > PasteFilterType;
  PasteFilterType::Pointer pasteFilter = PasteFilterType::New();
  typedef itk::MedianImageFilter< ImageType,
                                  ImageType > MedianFilterType;
  MedianFilterType::Pointer medianFilter = MedianFilterType::New();
  extractFilter->SetInput( inputImage );
  medianFilter->SetInput( extractFilter->GetOutput() );
  pasteFilter->SetSourceImage( medianFilter->GetOutput() );
  pasteFilter->SetDestinationImage( inputImage );
  pasteFilter->SetDestinationIndex( start );

  ImageType::SizeType indexRadius;
  indexRadius[0] = 1; // radius along x
  indexRadius[1] = 1; // radius along y
  indexRadius[2] = 0; // radius along z
  medianFilter->SetRadius( indexRadius );
  medianFilter->UpdateLargestPossibleRegion();
  const ImageType * medianImage = medianFilter->GetOutput();
  pasteFilter->SetSourceRegion( medianImage->GetBufferedRegion() );
  writer->SetInput( pasteFilter->GetOutput() );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
