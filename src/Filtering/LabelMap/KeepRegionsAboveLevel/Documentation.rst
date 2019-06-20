Keep Regions Above Certain Level
================================

.. index::
   single: LabelShapeKeepNObjectsImageFilter
   single: region
   pair: level; property

Synopsis
--------

Keep only regions that rank above a certain level of a particular property.


Results
-------
.. figure:: input.png
  :scale: 150%
  :alt: input.png

  Input image.

.. figure:: output.png
  :scale: 150%
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

.. breathelink:: itk::LabelShapeKeepNObjectsImageFilter
