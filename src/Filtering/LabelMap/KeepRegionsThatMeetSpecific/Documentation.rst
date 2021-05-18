:name: KeepRegionsThatMeetSpecific

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
  :scale: 70%
  :alt: input.png

  input.png

.. figure:: output.png
  :scale: 70%
  :alt: output.png

  output.png

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ShapeOpeningLabelMapFilter
