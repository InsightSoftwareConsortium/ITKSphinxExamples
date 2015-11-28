Generate Slices From Volume
===========================

.. index::
   single: ImageSeriesWriter
   single: NumericSeriesFileNames

Synopsis
--------

Create series of 2D images from a given volume.


Results
-------

.. figure:: Input.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: Output-20Baseline.png
  :scale: 200%
  :alt: Output image, slice 20

  Output image, slice 20

.. figure:: Output-30Baseline.png
  :scale: 200%
  :alt: Output image, slice 30

  Output image, slice 30


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

.. literalinclude:: Code.py
   :lines: 1, 20-

Classes demonstrated
--------------------

.. breathelink:: itk::NumericSeriesFileNames

.. breathelink:: itk::ImageSeriesWriter
