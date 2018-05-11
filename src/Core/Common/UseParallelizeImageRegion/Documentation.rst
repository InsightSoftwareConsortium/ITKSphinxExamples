Use ParallelizeImageRegion
==========================

.. index::
   single: MultiThreaderBase

Synopsis
--------


This example demonstrates how to use MultiThreaderBase::ParallelizeImageRegion
to apply a non-trivial operation for all pixels in an image in parallel.
Doing something like this in a multi-threaded way
before ITK 5.0 required a class to be created.


Results
-------


.. figure:: CellsFluorescence1Out.png
  :scale: 100%
  :alt: Segmentation and custom colorization.

  Segmentation and custom colorization of an image using
  MultiThreaderBase::ParallelizeImageRegion.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::MultiThreaderBase
