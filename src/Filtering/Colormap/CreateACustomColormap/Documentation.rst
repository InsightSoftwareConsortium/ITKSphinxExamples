:name: CreateACustomColormap

Create a Custom Color Map
=========================

.. index::
   single: CustomColormapFunction
   single: MersenneTwisterRandomVariateGenerator
   single: ScalarToRGBColormapImageFilter

Synopsis
--------

Create and apply a custom colormap.

.. note:: Python wrapping for CustomColormapFunction and the MersenneTwisterRandomVariateGenerator was introduced in ITK 4.8.0.


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

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::Function::CustomColormapFunction

.. breathelink:: itk::ScalarToRGBColormapImageFilter

.. breathelink:: itk::Statistics::MersenneTwisterRandomVariateGenerator
