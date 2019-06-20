Morphological Watershed Segmentation
====================================

.. index::
   single: MorphologicalWatershedImageFilter
   single: watershed
   pair: watershed; segmentation

Synopsis
--------

Morphological watershed segmentation.


Results
-------
.. figure:: input.png
  :scale: 150%
  :alt: input.png image generated

  Input image.

.. figure:: output_20_3.png
  :scale: 150%
  :alt: output_20_3.png image generated

  Output_20_3 image.

Output::

  Running with:
  Threshold: 20
  Level: 3

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MorphologicalWatershedImageFilter
