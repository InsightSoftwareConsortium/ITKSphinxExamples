:name: BresenhamLine

Bresenham Line
==============

.. index::
   single: BresenhamLine

Synopsis
--------

Get the points on a Bresenham line between two points.


Results
-------
.. figure:: Segmentation.png
  :scale: 70%
  :alt: Segmentation.png

  ITK's Bresenham's Line algorithm is used and optimized for voxel traversal operations.

.. figure:: Operation.png
  :scale: 70%
  :alt: Operation.png

Output::

  [0, 0]
  [1, 1]
  [2, 2]
  [3, 3]
  [0, 0]
  [1, 1]
  [2, 2]
  [3, 3]
  [4, 4]
  [5, 5]
  [6, 6]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::BresenhamLine
