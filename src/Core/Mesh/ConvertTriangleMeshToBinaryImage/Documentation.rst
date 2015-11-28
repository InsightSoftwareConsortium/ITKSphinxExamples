Convert Triangle Mesh To Binary Image
=====================================

.. index::
   single: TriangleMeshToBinaryImageFilter

Synopsis
--------

Convert a triangular itk::Mesh to binary itk::Image


Results
-------

.. figure:: ConvertTriangleMeshToBinaryImageInputs.png
  :scale: 80%
  :alt: Input image and mesh

  Input 3D Image and Mesh

.. figure:: Output.png
  :scale: 100%
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::TriangleMeshToBinaryImageFilter
