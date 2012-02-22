Bounding Box Of A Point Set
===========================

.. index::
   single: PointSet
   single: BoundingBox

Synopsis
--------


Get the bounding box of a PointSet


Results
-------


Output::
  bounds: [0, 0.1, 0, 0.1, 0, 0]
  center: [0.05, 0.05, 0]
  diagonal length squared: 0.02


Code
----

C++
...

.. literalinclude:: BoundingBoxOfAPointSet.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::PointSet itk::BoundingBox
