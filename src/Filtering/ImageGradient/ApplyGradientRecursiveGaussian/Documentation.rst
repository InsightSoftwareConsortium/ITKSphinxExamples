Apply GradientRecursiveGaussianImageFilter
==========================================

.. index::
   single: GradientRecursiveGaussianImageFilter
   single: RescaleIntensityImageFilter
   single: VectorIndexSelectionCastImageFilter
   single: VectorMagnitudeImageFilter

Synopsis
--------

Computes the gradient of an image by convolution with the first derivative of a Gaussian.

The output of the GradientRecursiveGaussianImageFilter is composed of two imagescomponents (gradients along the X and Y directions). In this example, we store these components using an image with CovariantVector pixel type. Covariant vectors are the natural representation for gradients since they are the equivalent of normals to iso-values manifolds.

This example shows also how to extract the X and Y gradients as images, and how to compute the magnitude of the CovariantVector image.

Note that the covariant vector types were only added to the VectorIndexSelectionCastImageFilter Python wrapping in ITK 4.7.

Results
-------

.. figure:: Gourds.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: ApplyGradientRecursiveGaussianTestOutputBaselineX.png
  :scale: 50%
  :alt: Gradient along X direction

  Gradient along X direction

.. figure:: ApplyGradientRecursiveGaussianTestOutputBaselineY.png
  :scale: 50%
  :alt: Gradient along Y direction

  Gradient along Y direction

.. figure:: ApplyGradientRecursiveGaussianTestOutputBaselineMagnitude.png
  :scale: 50%
  :alt: Output magnitude

  The image of the magnitude of the vector containing the X and Y values.


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-


Classes demonstrated
--------------------

.. breathelink:: itk::GradientRecursiveGaussianImageFilter
