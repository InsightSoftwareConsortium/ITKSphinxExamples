Label Binary Regions In Image
=============================

.. index::
   single: BinaryImageToLabelMapFilter
   pair: label; binary

Synopsis
--------

Label binary regions in an image.


Results
-------
.. figure:: image.png
  :scale: 1500%
  :alt: image.png image generated

  Image generated.

Output::

  There are 1 objects.
  Object 0 contains pixel [6, 6]
  Object 0 contains pixel [7, 6]
  Object 0 contains pixel [8, 6]
  Object 0 contains pixel [9, 6]
  Object 0 contains pixel [6, 7]
  Object 0 contains pixel [7, 7]
  Object 0 contains pixel [8, 7]
  Object 0 contains pixel [9, 7]
  Object 0 contains pixel [6, 8]
  Object 0 contains pixel [7, 8]
  Object 0 contains pixel [8, 8]
  Object 0 contains pixel [9, 8]
  Object 0 contains pixel [6, 9]
  Object 0 contains pixel [7, 9]
  Object 0 contains pixel [8, 9]
  Object 0 contains pixel [9, 9]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::BinaryImageToLabelMapFilter
