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

.. breathelink:: itk::LabelShapeKeepNObjectsImageFilter
