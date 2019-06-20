Iterate Region In Image With Neighborhood
=========================================

.. index::
   single: NeighborhoodIterator
   pair: iterate; region
   pair: image; neighborhood

Synopsis
--------

Iterate over a region of an image with a neighborhood (with write access).


Results
-------
.. figure:: Yinyang.png
  :scale: 60%
  :alt: input yin-yang image

  Input image.

.. figure:: IterateRegionWithWriteAccess.png
  :scale: 70%
  :alt: output in vtk window

  Output in VTK window.

Output::

  An extensive list of the neighborhood will be printed to the screen.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::NeighborhoodIterator
