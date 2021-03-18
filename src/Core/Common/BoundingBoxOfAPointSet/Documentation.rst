Bounding Box of a Point Set
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

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::PointSet itk::BoundingBox
