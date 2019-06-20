Add Constant To Every Pixel Without Duplicating Memory
======================================================

.. index::
   single: AddPixelAccessor
   pair: add; constant
   pair: without; duplication

Synopsis
--------

Add a constant to every pixel without duplicating the image in memory (an accessor).


Results
-------
Output::

  addPixelAccessor.SetValue(5)
  image->GetPixel[0, 0]: 20 adaptor->GetPixel[0, 0]: 25
  addPixelAccessor.SetValue(100)
  image->GetPixel[0, 0]: 20 adaptor->GetPixel[0, 0]: 120

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::AddPixelAccessor
