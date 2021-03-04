Extract Inner And Outer Boundaries Of Blobs In Binary Image
===========================================================

.. index::
   single: BinaryContourImageFilter
   single: blob
   pair: inner; outer

Synopsis
--------

Extract the inner and outer boundaries of blobs in a binary image.


Results
-------
.. figure:: ExtractBoundariesOfBlobsInBinaryImage.png
  :scale: 70%

  Output In VTK Window

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::BinaryContourImageFilter
