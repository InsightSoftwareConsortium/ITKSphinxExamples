Resample Segmented Image
========================

.. index::
   single: LabelImageGaussianInterpolateImageFunction
   pair: segmented; image

Synopsis
--------

Resample (stretch or compress) a segmented image.


Results
-------

.. figure:: Gourds.png
   :scale: 50%
   :alt: Input image.

   Input Image

.. figure:: ResampleSegmentedImageQuickview.png
   :scale: 50%
   :alt: QuickView output.

   Output In QuickView

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::LabelImageGaussianInterpolateImageFunction
