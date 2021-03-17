Is Pixel Inside Region
======================

.. index::
   single: ImageRegion
   pair: ImageRegion; IsInside
   single: Index
   single: Size

Synopsis
--------


Determine if a pixel is inside of a region


Results
-------

Output::

  [1, 1] Inside
  [6, 6] Outside

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

.. breathelink:: itk::ImageRegion
