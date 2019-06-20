Assign Contiguous Labels To Connected Regions In An Image
=========================================================

.. index::
   single: RelabelComponentImageFilter
   pair: connect; regions

Synopsis
--------

Assign contiguous labels to connected regions of an image.


Results
-------
.. figure:: AssignContiguousLabelsToConnectedRegions.png
  :scale: 60%
  :alt: output in vtk window

  Output in VTK window.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::RelabelComponentImageFilter
