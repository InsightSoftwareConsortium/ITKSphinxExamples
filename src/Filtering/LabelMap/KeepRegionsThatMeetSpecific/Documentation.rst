Keep Regions That Meet Specific Properties
==========================================

.. index::
   single: ShapeOpeningLabelMapFilter
   single: region
   pair: threshold; property

Synopsis
--------

Keep only regions that meet a specified threshold of a specified property.


Results
-------
.. figure:: input.png
  :scale: 150%
  :alt: input.png image generated

  Input image.

.. figure:: output.png
  :scale: 150%
  :alt: output.png image generated

  Output image.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ShapeOpeningLabelMapFilter
