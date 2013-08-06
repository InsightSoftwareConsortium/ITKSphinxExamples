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

Note that since the algorithm is based on the Hessian_, it will also identify
black tubular structures.

An important parameter is the `Sigma` that determines the amount of smoothing
applied during Hessian estimation.  A larger `Sigma` will decrease the
identification of noise or small structures as vessels.  In this example, the
`Sigma` is large enough only vessels comprising the `Circle of Willis`_ and
other large vessels are segmented.

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

.. _Hessian: http://en.wikipedia.org/wiki/Hessian_matrix
.. _Circle of Willis: http://en.wikipedia.org/wiki/Circle_of_Willis
