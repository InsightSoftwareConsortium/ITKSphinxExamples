Normalized Correlation
======================

.. index::
   single: NormalizedCorrelationImageFilter

Synopsis
--------

Normalized correlation.


Results
-------
.. figure:: Yinyang.png
  :scale: 60%
  :alt: input yin-yang image

  Input image.

.. figure:: correlation.png
  :scale: 60%
  :alt: correlation.png image generated

  Correlation image.

.. figure:: patch.png
  :scale: 600%
  :alt: patch.png image generated

  Patch image.

Output::

  Maximum: [0, 0]
  Dimension: 2
  Index: [-25, -25]
  Size: [51, 51]
  StreamableRegion region: ImageRegion (0x7ffee21eb4e8)
  Dimension: 2
  Index: [0, 0]
  Size: [512, 342]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::NormalizedCorrelationImageFilter
