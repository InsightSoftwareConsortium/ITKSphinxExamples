Create A Image Region
=====================

.. index::
   single: ImageRegion
   single: Index
   single: Size

Synopsis
--------


This class holds an Index (the "bottom left" corner of a region) and a Size (the size of the region). These two items together completely describe a region.


Results
-------

Output::
  ImageRegion (0x7fff45dad5c0)
  Dimension: 2
  Index: [1, 1]
  Size: [3, 3]


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageRegion
