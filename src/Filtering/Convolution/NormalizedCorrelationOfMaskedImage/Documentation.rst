Normalized Correlation Of Masked Image
======================================

.. index::
   single: NormalizedCorrelationImageFilter
   pair: correlation; masked
   pair: normalized; correlation

Synopsis
--------

Normalized correlation of a masked image.


Results
-------
.. figure:: mask.png
  :scale: 600%
  :alt: mask.png image generated

  Mask image.

.. figure:: image1.png
  :scale: 600%
  :alt: image1.png image generated

  Image 1.

.. figure:: image2.png
  :scale: 600%
  :alt: image2.png image generated

  Image 2.

.. figure:: NormalizedCorrelationOfMaskedImage.png
  :scale: 50%
  :alt: correlation.mha

  Correlation.mha

.. figure:: correlation.png
  :scale: 600%
  :alt: correlation.png image generated

  Correlation image.

Output::

  Maximum location fixed: [20, 6]
  Maximum value: 1

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::NormalizedCorrelationImageFilter
