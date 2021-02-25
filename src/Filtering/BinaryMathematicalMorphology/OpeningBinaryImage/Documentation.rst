:name: OpeningBinaryImage

Opening a Binary Image
======================

.. index::
   single: BinaryMorphologicalOpeningImageFilter
   single: binary; image

Synopsis
--------

Opening a binary image.


Results
-------
.. figure:: OpeningBinaryImageQuickView.png
  :scale: 70%

  Output In VTK Window

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
