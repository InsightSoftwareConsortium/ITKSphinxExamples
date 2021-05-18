:name: ApplyAFilterToASpecifiedRegionOfAnImage

Apply a Filter to a Specified Region of an Image
================================================

.. index::
   single: DerivativeImageFilter
   pair: derivative; image

Synopsis
--------

Computes the derivative of an image in a particular direction.


Results
-------
.. figure:: BrainProtonDensitySlice.png
   :scale: 50%
   :alt: Input image

   Input image

.. figure:: DerivativeImageQuickview.png
   :scale: 50%
   :alt: Output in QuickView

   Output in QuickView

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::DerivativeImageFilter
