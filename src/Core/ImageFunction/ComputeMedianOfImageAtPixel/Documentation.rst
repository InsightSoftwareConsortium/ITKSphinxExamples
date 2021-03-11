Compute Median of Image at Pixel
================================

.. index::
   single: MedianImageFunction
   pair: image; median
   single: function

Synopsis
--------

Computes the median of an image at a pixil(in a regular neighborhood).


Results
-------
.. figure:: ComputeMedianOfImageAtPixel.png
  :scale: 70%
  :alt: input.png

  input.png

Output::

  Median at [10, 10] is 0

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MedianImageFunction
