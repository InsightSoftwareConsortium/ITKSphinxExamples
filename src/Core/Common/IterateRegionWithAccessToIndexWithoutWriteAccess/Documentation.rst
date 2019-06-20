Iterate Region In Image With Access To Index Without Write Access
=================================================================

.. index::
   single: ImageRegionConstIteratorWithIndex
   pair: write; access
   single: index

Synopsis
--------

Iterate over a region of an image with efficient access to the current index (without write access).


Results
-------
.. figure:: Yinyang.png
  :scale: 60%
  :alt: input yin-yang image

  Input image.

.. figure:: IterateRegionWithAccessToIndexWithoutWriteAccess.png
  :scale: 100%
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

.. breathelink:: itk::ImageRegionConstIteratorWithIndex
