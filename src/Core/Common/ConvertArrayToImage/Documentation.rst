:name: ConvertArrayToImage

Convert Array to Image
======================

.. index::
   single: ImportImageFilter
   pair: array; convert
   pair: array; image

Synopsis
--------

Convert a C-style array to an itkImage.

.. figure:: Relationship.png
  :scale: 70%
  :alt: relationship.png

  Relationship between ProcessObjects and DataObjects


Results
-------
.. figure:: Sphere.png
  :scale: 70%
  :alt: sphere.png

  Slice of 3D image

.. figure:: Sphere3D.png
  :scale: 70%
  :alt: sphere.png

  3D volume rendering of 3D image

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ImportImageFilter
