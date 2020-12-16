Add Gaussian Noise to an Image
=====================================================

.. index::
   single: DerivativeImageFilter
   pair: image; random

Synopsis
--------

Adds Gaussian Noise to a particular image


Results
-------
.. figure:: Gourds.png
   :scale: 70%

   Input Image

.. figure:: OutputImage.png
   :scale: 70%

   Output Image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 18-

Classes demonstrated
--------------------

.. breathelink:: itk::AdditiveGaussianNoiseImageFilter
