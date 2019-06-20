Closing Binary Image
====================

.. index::
   single: BinaryMorphologicalClosingImageFilter
   pair: binary; image

Synopsis
--------

Closing a binary image.


Results
-------
.. figure:: ClosingBinaryImage
  :scale: 35%
  :alt: output in vtk window

  Output in VTK window.

Output::

  Radius: 5

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::BinaryMorphologicalClosingImageFilter
