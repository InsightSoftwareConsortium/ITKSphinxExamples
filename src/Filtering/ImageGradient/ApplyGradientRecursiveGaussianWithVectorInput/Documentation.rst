Apply GradientRecursiveGaussianImageFilter on Image with Vector type
====================================================================

.. index::
   single: GradientRecursiveGaussianImageFilter
   single: RescaleIntensityImageFilter
   single: VectorIndexSelectionCastImageFilter
   single: InvertIntensityImageFilter
   single: ComposeImageFilter

Synopsis
--------

Computes the gradient of an image by convolution with the first derivative of a Gaussian.

The output of the GradientRecursiveGaussianImageFilter is composed of two images (gradient along the X and Y directions). In this example, the input
is an image having two values per pixel (vector type). One value is coming
from the inputed image (first image); the second is the inverse of the inputed image (second image).

The output of GradientRecursiveGaussianImageFilter will then have four values per pixel. These are in the following order: gradient along X axis (first image), gradient along Y axis (first image), gradient along X axis (second image), gradient along Y axis (second image).

Note that the Python example will only work with ITK 4.8.0 or greater. The ComoposeImagefilter could be used to cast
from unsigned char to double type without explicitely using the CastImageFilter; but in Python this possibilty is
not allowed. This reduces the number of combinations that need to be wrapped, which helps reducing the size of the ITK binaries.

Results
-------

.. figure:: Gourds.png
  :scale: 50%
  :alt: Input image

  Input image (first image)

.. figure:: ApplyGradientRecursiveGaussianWithVectorInputTestOutputBaseline1X.png
  :scale: 50%
  :alt: Gradient along X direction (first image)

  Gradient along X direction (first image)

.. figure:: ApplyGradientRecursiveGaussianWithVectorInputTestOutputBaseline1Y.png
  :scale: 50%
  :alt: Gradient along Y direction (first image)

  Gradient along Y direction (first image)

.. figure:: ApplyGradientRecursiveGaussianWithVectorInputTestOutputBaseline2X.png
  :scale: 50%
  :alt: Gradient along X direction (second image)

  Gradient along X direction (second image)

.. figure:: ApplyGradientRecursiveGaussianWithVectorInputTestOutputBaseline2Y.png
  :scale: 50%
  :alt: Gradient along Y direction (second image)

  Gradient along Y direction (second image)


Code
----

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::GradientRecursiveGaussianImageFilter
