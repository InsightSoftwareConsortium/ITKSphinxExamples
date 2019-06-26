Upsample An Image
=======================================

.. index::
   single: ResampleImageFilter
   single: LinearInterpolateImageFunction
   single: ScaleTransform
   single: BSplineInterpolateImageFunction
   single: Upsampling

Synopsis
--------

Upsample an image.


Results
-------

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: BrainProtonDensitySlice.png
  :scale: 50%
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

.. breathelink:: itk::ResampleImageFilter
.. breathelink:: itk::BSplineInterpolateImageFunction
