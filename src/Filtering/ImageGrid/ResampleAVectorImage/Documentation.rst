Resample A Vector Image
=======================

.. index::
   single: ResampleImageFilter
   single: IdentityTransform
   single: LinearInterpolateImageFunction

Synopsis
--------

Linearly interpolate a vector image.

The Python wrapping for the LinearInterpolateImageFunction using vector images was added in ITK 4.7.0.


Results
-------

.. figure:: VisibleWomanHeadSlice.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image


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

.. breathelink:: itk::ResampleImageFilter
