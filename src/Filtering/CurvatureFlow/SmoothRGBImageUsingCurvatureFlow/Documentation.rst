:name: SmoothRGBImageUsingCurvatureFlow

Smooth RGB Image Using Curvature Flow
=====================================

.. index::
   single: CurvatureFlowImageFilter
   pair: curvature; flow
   single: RGB

Synopsis
--------

Smooth an RGB image using curvature flow.


Results
-------
.. figure:: Gourds.png
  :scale: 70%
  :alt: input image

  Input image.

.. figure:: SmoothRGBImageUsingCurvatureFlow.png
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

.. breathelink:: itk::CurvatureFlowImageFilter
