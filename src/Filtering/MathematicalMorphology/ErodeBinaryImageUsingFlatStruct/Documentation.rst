Erode Binary Image Using Flat Structure Element
===============================================

.. index::
   single: FlatStructuringElement
   pair: binary; image

Synopsis
--------

Erode a binary image using a flat (box) structuring element.


Results
-------
.. figure:: ErodeBinaryImageUsingFlatStruct.png
  :scale: 55%
  :alt: output in vtk window

  Input and output image when radius = 7.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::FlatStructuringElement
