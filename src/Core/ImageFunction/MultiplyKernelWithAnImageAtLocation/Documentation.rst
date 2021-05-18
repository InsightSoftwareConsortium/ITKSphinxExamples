:name: MultiplyKernelWithAnImageAtLocation

Multiply Kernel With an Image at Location
=========================================

.. index::
   single: NeighborhoodOperatorImageFunction
   pair: kernel; image
   single: location

Synopsis
--------

This will multiply a kernel with an image at a particular location.


Results
-------
Output::

  Sum on border: 4
  Sum in center: 9
  Sum outside: 0

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::NeighborhoodOperatorImageFunction
