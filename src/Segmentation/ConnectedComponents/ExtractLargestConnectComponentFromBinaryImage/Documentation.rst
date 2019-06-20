Extract Largest Connect Component From Binary Image
===================================================

.. index::
   single: ConnectedComponentImageFilter
   pair: binary; image
   pair: extract; component

Synopsis
--------

Extract the largest connected component from a Binary Image.


Results
-------
.. figure:: ExtraLargestConnectComponentFromBinaryImage.png
  :scale: 50%
  :alt: output in vtk window

  Output in VTK window.

Output::

  Number of objects: 3


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ConnectedComponentImageFilter
