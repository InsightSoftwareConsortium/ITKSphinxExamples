:name: KeepBinaryRegionsThatMeetSpecific

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
  :scale: 70%
  :alt: input.mhd

  input.mhd

.. figure:: output.png
  :scale: 70%
  :alt: output.mhd

  output.mhd

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::BinaryStatisticsOpeningImageFilter
