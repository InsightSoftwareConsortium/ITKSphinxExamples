Try Catch Exception
===================

.. index::
   single: ExceptionObject

Synopsis
--------


Try and catch an itk Exception


Results
-------

Output::
  ExceptionObject caught !

  itk::ImageFileReaderException (0x20cece0)
  Location: "void itk::ImageFileReader<TOutputImage, ConvertPixelTraits>::GenerateOutputInformation() [with TOutputImage = itk::Image<double, 2u>, ConvertPixelTraits = itk::DefaultConvertPixelTraits<double>]"
  File: /path/to/ITK/Modules/IO/ImageBase/include/itkImageFileReader.hxx
  Line: 143
  Description:  Could not create IO object for file nofile.png
  The file doesn't exist.
  Filename = nofile.png

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ExceptionObject
