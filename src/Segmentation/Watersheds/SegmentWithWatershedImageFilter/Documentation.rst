Watershed Image Filter
======================

.. index::
   single: WatershedImageFilter

Synopsis
--------

This example illustrates how to segment an image using the watershed method.

Results
-------

.. figure:: BrainProtonDensitySlice.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: SegmentWithWatershedImageFilterTest02Baseline.png
  :scale: 50%
  :alt: Segmented image

  Segmented image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :language: c++
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-


Classes demonstrated
--------------------

.. breathelink:: itk::WatershedImageFilter
