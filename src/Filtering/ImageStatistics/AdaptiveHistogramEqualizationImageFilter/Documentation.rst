:name: AdaptiveHistogramEqualizationImageFilter

Adaptive Histogram Equalization Image Filter
============================================

.. index::
   single: AdaptiveHistogramEqualizationImageFilter
   single: smooth

Synopsis
--------

Apply a power law adaptive histogram equalization controlled by the parameters
alpha and beta.

The parameter ``alpha`` controls how much the filter acts like the classical
histogram equalization method (``alpha = 0``) to how much the filter acts like
an unsharp mask (``alpha = 1``).

The parameter ``beta`` controls how much the filter acts like an unsharp mask
(``beta = 0``) to much the filter acts like pass through (``beta = 1, with
alpha = 1``).

The parameter window (or radius) controls the size of the region
over which local statistics are calculated.

Results
-------

.. |input_image| image:: sf4.png
   :align: middle
   :alt: Input image

.. |input_image_histogram| image:: sf4_histogram.png
   :align: middle
   :alt: Input image histogram

.. |output_image| image:: AdaptiveHistogramEqualizationImageFilter06Baseline.png
   :align: middle
   :alt: Output image

.. |output_image_histogram| image:: AdaptiveHistogramEqualizationImageFilter06Baseline_histogram.png
   :align: middle
   :alt: Output image histogram

.. |input_image_caption| replace:: Input image.
.. |input_image_histogram_caption| replace:: Input image histogram.
.. |output_image_caption| replace:: Output image.
.. |output_image_histogram_caption| replace:: Output image histogram.

.. tabularcolumns:: |c|c|

===================================   ====================================
            |input_image|                       |output_image|
         |input_image_caption|              |output_image_caption|
-----------------------------------   ------------------------------------
       |input_image_histogram|             |output_image_histogram|
   |input_image_histogram_caption|     |output_image_histogram_caption|
===================================   ====================================


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
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::AdaptiveHistogramEqualizationImageFilter
