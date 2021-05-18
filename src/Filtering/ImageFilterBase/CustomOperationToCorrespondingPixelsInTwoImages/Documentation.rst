:name: CustomOperationToCorrespondingPixelsInTwoImages

Custom Operation to Corresponding Pixels in Two Images
======================================================

.. index::
   single: BinaryFunctorImageFilter
   pair: corresponding; pixels
   pair: custom; operation

Synopsis
--------

Apply a predefined operation to corresponding pixels in two images.


Results
-------
Output::

  pixel1 was = 2
  pixel2 was = 5
  output is = 9

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::BinaryFunctorImageFilter
