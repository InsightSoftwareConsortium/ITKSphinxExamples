Apply Affine Transform From Homogeneous Matrix And Resample
===========================================================

.. index::
   single: AffineTransform
   single: WindowedSincInterpolateImageFunction
   single: ResampleImageFilter

Synopsis
--------

Given one homogeneous matrix (here a 3x3 matrix), apply the corresponding
transform to a given image and resample using a
WindowedSincInterpolateImageFunction.

Results
-------

.. figure:: Gourds.png
  :scale: 50%
  :alt: Input image

  Input image.

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image.


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::AffineTransform
.. breathelink:: itk::WindowedSincInterpolateImageFunction
.. breathelink:: itk::ResampleImageFilter
