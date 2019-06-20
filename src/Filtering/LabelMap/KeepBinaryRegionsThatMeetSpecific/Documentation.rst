Keep Binary Regions That Meet Specific Properties
=================================================

.. index::
   single: BinaryStatisticsOpeningImageFilter
   single: binary
   pair: binary; property
   pair: threshold; property

Synopsis
--------

Keep only regions that meet a specified threshold of a specified property.


Results
-------
.. figure:: input.png
  :scale: 50%
  :alt: input.mhd

  Input

.. figure:: output.png
  :scale: 50%
  :alt: output.mhd

  Output

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::BinaryStatisticsOpeningImageFilter
