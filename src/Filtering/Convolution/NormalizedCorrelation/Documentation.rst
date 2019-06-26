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
  :scale: 70%
  :alt: Yinyang.png

  Yinyang.png

.. figure:: correlation.png
  :scale: 70%
  :alt: correlation.png

  correlation.png

.. figure:: patch.png
  :scale: 70%
  :alt: patch.png

  patch.png

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
