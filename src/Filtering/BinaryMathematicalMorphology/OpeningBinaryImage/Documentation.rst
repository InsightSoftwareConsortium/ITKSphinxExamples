Opening A Binary Image
======================

.. index::
   single: BinaryMorphologicalOpeningImageFilter
   single: binary; image

Synopsis
--------

Opening a binary image.


Results
-------
.. figure:: OpeningBinaryImage.png
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

.. breathelink:: itk::BinaryMorphologicalOpeningImageFilter
