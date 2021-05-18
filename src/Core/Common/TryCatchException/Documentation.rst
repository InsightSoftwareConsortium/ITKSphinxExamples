:name: TryCatchException

Try Catch Exception
===================

.. index::
   single: ExceptionObject

Synopsis
--------

Try and catch an `itk::ExceptionObject`. The exception is printed to console
output. This can provide more information when a program crashes, including
where the exception occurred and its description. Exceptions in ITK are
usually only thrown during calls to `->Update()`, so only the `->Update()`
call is added to the `try` block.


Results
-------

.. code-block:: none

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
