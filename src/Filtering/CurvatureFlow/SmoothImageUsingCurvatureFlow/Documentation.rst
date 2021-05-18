:name: SmoothImageUsingCurvatureFlow

Smooth Image Using Curvature Flow
=================================

.. index::
   single: CurvatureFlowImageFilter
   pair: curvature; flow
   single: smooth

Synopsis
--------

Smooth an image using curvature flow.


Results
-------
.. figure:: Yinyang.png
  :scale: 70%
  :alt: input image

  Input image.

.. figure:: SmoothImageUsingCurvatureFlow.png
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
