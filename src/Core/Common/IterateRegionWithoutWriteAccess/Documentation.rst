Iterate Region In Image Without Write Access
============================================

.. index::
   single: ImageRegionConstIterator
   pair: write; access

Synopsis
--------

Iterate over a region of an image (without write access).


Results
-------
.. figure:: Yinyang.png
  :scale: 70%

  Yinyang.png

Output::

  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255
  255

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ImageRegionConstIterator
