Segment Blood Vessels
=====================

.. index::
   single: Hessian3DToVesselnessMeasureImageFilter
   pair: segment; vessel
   pair: segment; tube

Synopsis
--------

The example takes an image (say MRA image), computes the vesselness measure
of the image using the HessianRecursiveGaussianImageFilter and the
Hessian3DToVesselnessMeasureImageFilter. The goal is to detect bright, tubular
structures in the image.

Results
-------

.. figure:: Input.png
  :scale: 70%
  :alt: Input image

  Input head MRA.

.. figure:: Output.png
  :scale: 70%
  :alt: Output image

  Output vessel segmentation.


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::Hessian3DToVesselnessMeasureImageFilter

.. breathelink:: itk::HessianRecursiveGaussianImageFilter
