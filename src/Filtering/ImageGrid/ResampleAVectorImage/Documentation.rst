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

.. figure::
  :scale: 50%
  :alt: Input image

  Input image

.. figure::
  :scale: 50%
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: Code.cxx

Python
......

.. literalinclude:: Code.py


Classes demonstrated
--------------------

.. breathelink:: itk::ResampleImageFilter
