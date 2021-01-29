Smooth Binary Image Before Surface Extraction
=============================================

.. index::
   single: AntiAliasBinaryImageFilter
   single: smooth

Synopsis
--------

This example introduces the use of the `AntiAliasBinaryImageFilter`. This
filter expects a binary mask as input. With level sets, it smooths the image
by keeping the edge of the structure within a one pixel distance from the
original location. It is usually desirable to run this filter before
extracting an isocontour with surface extraction methods.


Results
-------

.. figure:: VentricleModel.png
  :scale: 100%
  :alt: Input image

  Input image

.. figure:: Output.png
  :scale: 100%
  :alt: Output image

  Output image


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

.. breathelink:: itk::AntiAliasBinaryImageFilter
