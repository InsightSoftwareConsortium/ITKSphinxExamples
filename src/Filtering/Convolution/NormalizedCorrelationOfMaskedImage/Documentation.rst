:name: NormalizedCorrelationOfMaskedImage

Normalized Correlation of Masked Image
======================================

.. index::
   single: NormalizedCorrelationImageFilter
   pair: correlation; masked

Synopsis
--------

Normalized correlation of a masked image.


Results
-------
.. figure:: mask.png
  :scale: 70%
  :alt: mask.png

  mask.png

.. figure:: image1.png
  :scale: 70%
  :alt: image1.png

  image1.png

.. figure:: image2.png
  :scale: 70%
  :alt: image2.png

  image2.png

.. figure:: NormalizedCorrelationOfMaskedImage.png
  :scale: 70%
  :alt: correlation.mha

  correlation.mha

.. figure:: correlation.png
  :scale: 70%
  :alt: correlation.png

  correlation.png

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
