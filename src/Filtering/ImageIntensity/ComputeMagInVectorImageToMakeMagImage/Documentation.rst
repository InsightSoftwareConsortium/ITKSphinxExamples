Compute Magnitude In Vector Image To Make Magnitude Image
=========================================================

.. index::
   single: VectorMagnitudeImageFilter
   pair: magnitude; image
   pair: vector; image

Synopsis
--------

Compute the magnitude of each pixel in a vector image to produce a magnitude image


Results
-------
.. figure:: Yinyang.png
  :scale: 60%
  :alt: Yinyang.png

  Input image.

.. figure:: ComputerMagInVectorImageToMakeMagImage
  :scale: 70%
  :alt: output.png

  Output image.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::VectorMagnitudeImageFilter
