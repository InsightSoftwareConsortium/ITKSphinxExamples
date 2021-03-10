Resample Segmented Image
========================

.. index::
   single: LabelImageGaussianInterpolateImageFunction
   pair: segmented; image

Synopsis
--------

Resample (stretch or compress) a label image resulting form segmentation.

For more on why label image interpolation is necessary and how it works, see the `associated Insight Journal article <https://www.insight-journal.org/browse/publication/705>`_.


Results
-------

.. figure:: 2th_cthead1.png
   :scale: 50%
   :alt: Input label image.

   Input label image

.. figure:: OutputBaseline.png
   :scale: 50%
   :alt: QuickView output.

   Resample with label image gaussian interpolation.

.. figure:: OutputNearestBaseline.png
   :scale: 50%
   :alt: QuickView output.

   Resample with nearest neighbor interpolation.

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

.. breathelink:: itk::LabelImageGaussianInterpolateImageFunction
