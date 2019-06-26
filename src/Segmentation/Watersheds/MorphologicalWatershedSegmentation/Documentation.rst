Morphological Watershed Segmentation
====================================

.. index::
   single: MorphologicalWatershedImageFilter
   single: watershed

Synopsis
--------

Morphological watershed segmentation.


Results
-------
.. figure:: input.png
  :scale: 70%
  :alt: input.png

  input.png

.. figure:: output_20_3.png
  :scale: 70%
  :alt: output_20_3.png

  output_20_3.png

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
