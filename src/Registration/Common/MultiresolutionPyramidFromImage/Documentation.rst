:name: MultiresolutionPyramidFromImage

Multiresolution Pyramid From Image
==================================

.. index::
   single: RecursiveMultiResolutionPyramidImageFilter

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
  :scale: 70%
  :alt: output_0.png

  output_0.png

.. figure:: output_1.png
  :scale: 70%
  :alt: output_1.png

  output_1.png

.. figure:: output_2.png
  :scale: 70%
  :alt: output_2.png

  output_2.png

.. figure:: output_3.png
  :scale: 70%
  :alt: output_3.png

  output_3.png


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::RecursiveMultiResolutionPyramidImageFilter
