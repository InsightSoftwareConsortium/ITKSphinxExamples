Smooth RGB Image Using Min Max Curvature Flow
=============================================

.. index::
   single: MinMaxCurvatureFlowImageFilter
   single: RGB
   pair: curvature; flow
   pair: min; max

Synopsis
--------

Smooth an RGB image using min/max curvature flow.


Results
-------
.. figure:: SmoothRGBImageUsingMinMaxCurvatureFlow.png
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
