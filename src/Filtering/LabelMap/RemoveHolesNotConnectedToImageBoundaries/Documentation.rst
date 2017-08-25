Remove Holes Not Connected To Image Boundaries
==============================================

.. index::
   single: BinaryFillholeImageFilter

Synopsis
--------

Remove holes in one binary image not connected to its boundary. In this case
the foreground value for the image is taken to be zero (black), and everything
is filled in within the black boundary.


Results
-------

.. figure:: Yinyang.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
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
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::BinaryFillholeImageFilter
