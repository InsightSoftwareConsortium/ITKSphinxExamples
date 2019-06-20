Iterate Region In Image With Write Access
=========================================

.. index::
   single: ImageRegionIterator
   pair: iterate; region
   pair: write; access

Synopsis
--------

Iterate over a region of an image (with write access).


Results
-------
.. figure:: Yinyang.png
  :scale: 60%
  :alt: input yin-yang image

  Input image.

.. figure:: IterateRegionWithWriteAccess.png
  :scale: 100%
  :alt: output in VTK window

  Output in VTK window.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ImageRegionIterator
