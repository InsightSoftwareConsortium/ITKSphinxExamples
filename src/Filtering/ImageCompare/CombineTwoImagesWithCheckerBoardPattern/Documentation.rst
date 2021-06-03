:name: CombineTwoImagesWithCheckerBoardPattern

Combine Two Images With Checker Board Pattern
=============================================

.. index::
   single: CheckerBoardImageFilter

Synopsis
--------


Combine two images by alternating blocks of a checkerboard pattern.

In this example the first image is black and the second one is white.

Results
-------

.. figure:: OutputBaseline.png
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

.. breathelink:: itk::CheckerBoardImageFilter
