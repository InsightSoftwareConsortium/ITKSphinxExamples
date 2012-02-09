Compute Histogram From Grayscale Image
======================================

.. index::
  single: ImageToHistogramFilter

Synopsis
--------

Compute a histogram from a grayscale image

Results
-------

.. figure:: sf4.png
  :scale: 100%
  :alt: Input grayscale image.

  Input grayscale image.

Output::

  Frequency = [ 0,
  8593,
  17734,
  11515,
  5974,
  2225,
  2400,
  3422,
  3531,
  3283,
  2125,
  2628,
  1954,
  152,
  0,
  0 ]


Code
----

C++
...

.. literalinclude:: ComputeHistogramFromGrayscaleImage.cxx

Classes demonstrated
--------------------

.. doxygenclass:: itk::Statistics::ImageToHistogramFilter
  :no-link:

* Detailed documentation: :itkdox:`itk::Statistics::ImageToHistogramFilter`
