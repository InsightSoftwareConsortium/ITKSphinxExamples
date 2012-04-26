Create An Apply Custom Color Map
================================

.. index::
   single: CustomColormapFunction
   single: MersenneTwisterRandomVariateGenerator
   single: ScalarToRGBColormapImageFilter

Synopsis
--------


Create and apply a custom colormap


Results
-------

.. figure:: sf4.png
  :alt: Input image

  Input image

.. figure:: CreateAnApplyCustomColorMapOutputBaseline.png
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: CreateAnApplyCustomColorMap.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::Function::CustomColormapFunction

.. breathelink:: itk::ScalarToRGBColormapImageFilter

.. breathelink:: itk::Statistics::MersenneTwisterRandomVariateGenerator
