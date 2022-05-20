:name: DerivativeImage

Compute Derivative
=================

.. index::
   single: DerivativeImageFilter

Synopsis
--------

This filter computes a n-th Derivative of a scalar-valued image in a specified direction.


Results
-------

.. figure:: BrainProtonDensitySlice.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: Output.mha
  :scale: 50%
  :alt: Output image

  Output image


.. figure:: Output_normalized.mha
  :scale: 50%
  :alt: Output normalized image

  Output normalized image

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::DerivativeImageFilter
