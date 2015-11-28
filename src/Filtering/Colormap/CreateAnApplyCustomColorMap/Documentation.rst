Create An Apply Custom Color Map
================================

.. index::
   single: CustomColormapFunction
   single: MersenneTwisterRandomVariateGenerator
   single: ScalarToRGBColormapImageFilter

Synopsis
--------

Create and apply a custom colormap.

Note: The wrapping for Python of the CustomColormapFunction and the MersenneTwisterRandomVariateGenerator were introduced in ITK 4.8.0.


Results
-------

.. figure:: sf4.png
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
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
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::Function::CustomColormapFunction

.. breathelink:: itk::ScalarToRGBColormapImageFilter

.. breathelink:: itk::Statistics::MersenneTwisterRandomVariateGenerator
