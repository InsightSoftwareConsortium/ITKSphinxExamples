/*=========================================================================
 *
 *  Copyright NumFOCUS
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

//  This example illustrates how to read a DICOM series into a volume and then
//  print most of the DICOM header information. The binary fields are skipped.

#include "itkImageSeriesReader.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " DicomDirectory " << std::endl;
    return EXIT_FAILURE;
  }

  //  Next, we instantiate the type to be used for storing the image once it is
  //  read into memory.
  using PixelType = signed short;
  constexpr unsigned int Dimension = 3;

  using ImageType = itk::Image<PixelType, Dimension>;

  // We use the image type for instantiating the series reader type and then we
  // construct one object of this class.
  using ReaderType = itk::ImageSeriesReader<ImageType>;

  auto reader = ReaderType::New();

  // A GDCMImageIO object is created and assigned to the reader.
  using ImageIOType = itk::GDCMImageIO;

  auto dicomIO = ImageIOType::New();

  reader->SetImageIO(dicomIO);

  // A GDCMSeriesFileNames is declared in order to generate the names of DICOM
  // slices. We specify the directory with the SetInputDirectory() method
  // and, in this case, take the directory name from the command line arguments.
  // You could have obtained the directory name from a file dialog in a GUI.

  using NamesGeneratorType = itk::GDCMSeriesFileNames;

  auto nameGenerator = NamesGeneratorType::New();

  nameGenerator->SetInputDirectory(argv[1]);

  // The list of files to read is obtained from the name generator by invoking
  // the GetInputFileNames() method and receiving the results in a
  // container of strings. The list of filenames is passed to the reader using
  // the SetFileNames() method.
  using FileNamesContainer = std::vector<std::string>;
  FileNamesContainer fileNames = nameGenerator->GetInputFileNames();

  reader->SetFileNames(fileNames);

  // We trigger the reader by invoking the Update() method. This
  // invocation should normally be done inside a try/catch block given
  // that it may eventually throw exceptions.
  try
  {
    reader->Update();
  }
  catch (const itk::ExceptionObject & ex)
  {
    std::cout << ex << std::endl;
    return EXIT_FAILURE;
  }

  // ITK internally queries GDCM and obtains all the DICOM tags from the file
  // headers. The tag values are stored in the MetaDataDictionary
  // which is a general-purpose container for \{key,value\} pairs. The Metadata
  // dictionary can be recovered from any ImageIO class by invoking the
  // GetMetaDataDictionary() method.
  using DictionaryType = itk::MetaDataDictionary;

  const DictionaryType & dictionary = dicomIO->GetMetaDataDictionary();

  // In this example, we are only interested in the DICOM tags that can be
  // represented as strings. Therefore, we declare a MetaDataObject of
  // string type in order to receive those particular values.
  using MetaDataStringType = itk::MetaDataObject<std::string>;

  // The metadata dictionary is organized as a container with its corresponding
  // iterators. We can therefore visit all its entries by first getting access to
  // its Begin() and End() methods.
  auto itr = dictionary.Begin();
  auto end = dictionary.End();

  // We are now ready for walking through the list of DICOM tags. For this
  // purpose we use the iterators that we just declared. At every entry we
  // attempt to convert it into a string entry by using the dynamic_cast
  // based on RTTI information. The
  // dictionary is organized like a std::map structure, so we should use
  // the first and second members of every entry in order
  // to get access to the \{key,value\} pairs.
  while (itr != end)
  {
    itk::MetaDataObjectBase::Pointer entry = itr->second;

    MetaDataStringType::Pointer entryvalue = dynamic_cast<MetaDataStringType *>(entry.GetPointer());

    if (entryvalue)
    {
      std::string tagkey = itr->first;
      std::string tagvalue = entryvalue->GetMetaDataObjectValue();
      std::cout << tagkey << " = " << tagvalue << std::endl;
    }

    ++itr;
  }

  //  It is also possible to query for specific entries instead of reading all of
  //  them as we did above. In this case, the user must provide the tag
  //  identifier using the standard DICOM encoding. The identifier is stored in a
  //  string and used as key in the dictionary.
  std::string entryId = "0010|0010";

  auto tagItr = dictionary.Find(entryId);

  if (tagItr == end)
  {
    std::cerr << "Tag " << entryId;
    std::cerr << " not found in the DICOM header" << std::endl;
    return EXIT_FAILURE;
  }

  // Since the entry may or may not be of string type we must again use a
  // dynamic_cast in order to attempt to convert it to a string dictionary
  // entry. If the conversion is successful, we can then print out its content.
  MetaDataStringType::ConstPointer entryvalue = dynamic_cast<const MetaDataStringType *>(tagItr->second.GetPointer());

  if (entryvalue)
  {
    std::string tagvalue = entryvalue->GetMetaDataObjectValue();
    std::cout << "Patient's Name (" << entryId << ") ";
    std::cout << " is: " << tagvalue << std::endl;
  }
  else
  {
    std::cerr << "Entry was not of string type" << std::endl;
    return EXIT_FAILURE;
  }

  // This type of functionality will probably be more useful when provided
  // through a graphical user interface. For a full description of the DICOM
  // dictionary please look at the following file.

  return EXIT_SUCCESS;
}
