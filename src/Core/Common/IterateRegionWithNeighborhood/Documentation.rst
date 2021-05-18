:name: IterateRegionWithNeighborhood

Iterate Region in Image With Neighborhood
=========================================

.. index::
   single: NeighborhoodIterator
   pair: iterate; region

Synopsis
--------

Iterate over a region of an image with a neighborhood (with write access).


Results
-------
.. figure:: Yinyang.png
  :scale: 70%

  Yinyang.png

.. figure:: IterateRegionWithWriteAccess.png
  :scale: 70%

  Yinyang.png In VTK Window

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
