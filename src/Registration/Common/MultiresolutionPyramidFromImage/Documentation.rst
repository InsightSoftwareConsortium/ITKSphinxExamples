Multi-resolution Pyramid From Image
===================================

.. index::
   single: RecursiveMultiResolutionPyramidImageFilter
   pair: multi-resolution; pyramid

Synopsis
--------

Construct a multiresolution pyramid from an image.


Results
-------
Output::

  Writing output_0.png
  Writing output_1.png
  Writing output_2.png
  Writing output_3.png

.. figure:: output_0.png
  :scale: 1250%
  :alt: output_0.png generated image

  Output 0 image.

.. figure:: output_1.png
  :scale: 1250%
  :alt: output_1.png generated image

  Output 1 image.

.. figure:: output_2.png
  :scale: 1250%
  :alt: output_2.png generated image

  Output 2 image.

.. figure:: output_3.png
  :scale: 1250%
  :alt: output_3.png generated image

  Output 3 image.


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::RecursiveMultiResolutionPyramidImageFilter
