:name: ImageBufferAndIndexRange

Image Buffer and Index Range
============================

.. index::
   single: ImageBufferRange

Synopsis
--------


This example demonstrates how to iterate over all pixels of the buffered region
of an image, using either an iterator-based algorithm from the C++ Standard
Library, or a range-based for loop.


Results
-------

Output::

  Region index: [100, 200]; Region size: [4, 5]

  Pixel index: [100, 200]; Pixel value: 0
  Pixel index: [101, 200]; Pixel value: 1
  Pixel index: [102, 200]; Pixel value: 2
  Pixel index: [103, 200]; Pixel value: 3
  Pixel index: [100, 201]; Pixel value: 4
  Pixel index: [101, 201]; Pixel value: 5
  Pixel index: [102, 201]; Pixel value: 6
  Pixel index: [103, 201]; Pixel value: 7
  Pixel index: [100, 202]; Pixel value: 8
  Pixel index: [101, 202]; Pixel value: 9
  Pixel index: [102, 202]; Pixel value: 10
  Pixel index: [103, 202]; Pixel value: 11
  Pixel index: [100, 203]; Pixel value: 12
  Pixel index: [101, 203]; Pixel value: 13
  Pixel index: [102, 203]; Pixel value: 14
  Pixel index: [103, 203]; Pixel value: 15
  Pixel index: [100, 204]; Pixel value: 16
  Pixel index: [101, 204]; Pixel value: 17
  Pixel index: [102, 204]; Pixel value: 18
  Pixel index: [103, 204]; Pixel value: 19

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageBufferRange itk::IndexRange
