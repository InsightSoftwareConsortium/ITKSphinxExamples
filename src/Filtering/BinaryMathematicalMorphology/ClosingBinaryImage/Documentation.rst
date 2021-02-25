:name: ClosingBinaryImage

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

.. figure:: ClosingBinaryImageQuickView.png
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

.. breathelink:: itk::BinaryMorphologicalClosingImageFilter
