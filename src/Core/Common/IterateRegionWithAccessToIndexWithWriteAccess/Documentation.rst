:name: IterateRegionWithAccessToIndexWithWriteAccess

Iterate Region in Image With Access to Current Index With Write Access
======================================================================

.. index::
   single: ImageRegionIteratorWithIndex
   pair: write; access
   single: index

Synopsis
--------

Iterate over a region of an image with efficient access to the current index (with write access).


Results
-------
.. figure:: Yinyang.png
  :scale: 70%

  Yinyang.png

.. figure:: IterateRegionWithAccessToIndexWithWriteAccess.png
  :scale: 70%

  Yinyang.png In VTK Window With Index Access

Output::

  Indices:
  Index: [0, 0] value: ?
  Index: [1, 0] value: ?
  Index: [2, 0] value: ?
  Index: [3, 0] value: ?
  Index: [4, 0] value: ?
  Index: [0, 1] value: ?
  Index: [1, 1] value: ?
  Index: [2, 1] value: ?
  Index: [3, 1] value: ?
  Index: [4, 1] value: ?
  Index: [0, 2] value: ?
  Index: [1, 2] value: ?
  Index: [2, 2] value: ?
  Index: [3, 2] value: ?
  Index: [4, 2] value: ?
  Index: [0, 3] value: ?
  Index: [1, 3] value: ?
  Index: [2, 3] value: ?
  Index: [3, 3] value: ?
  Index: [4, 3] value: ?

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ImageRegionIteratorWithIndex
