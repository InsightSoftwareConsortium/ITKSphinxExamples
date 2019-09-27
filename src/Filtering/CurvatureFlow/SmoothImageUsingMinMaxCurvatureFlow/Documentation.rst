Smooth Image Using Min Max Curvature Flow
=========================================

.. index::
   single: MinMaxCurvatureFlowImageFilter
   pair: curvature; flow
   pair: min; max

Synopsis
--------

Smooth an image using min/max curvature flow.


Results
-------
.. figure:: Gourds.png
  :scale: 70%
  :alt: input image

  Input image.

.. figure:: SmoothImageUsingMinMaxCurvatureFlow.png
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

.. breathelink:: itk::MinMaxCurvatureFlowImageFilter
