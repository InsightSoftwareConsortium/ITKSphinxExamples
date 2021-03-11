Segment Blood Vessels With Multi-Scale Hessian-Based Measure
============================================================

.. index::
   single: MultiScaleHessianBasedMeasureImageFilter
   pair: segment; vessel
   pair: segment; tube

Synopsis
--------

Segment blood vessels with multi-scale Hessian-based measure.


Results
-------

.. figure:: Sidestream_dark_field_image.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image


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

.. breathelink:: itk::MultiScaleHessianBasedMeasureImageFilter
