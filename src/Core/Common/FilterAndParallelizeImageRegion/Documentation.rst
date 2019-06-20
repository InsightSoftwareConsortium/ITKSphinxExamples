Filter and ParallelizeImageRegion Comparison
============================================

.. index::
   single: MultiThreaderBase
   pair: filter; ParallelizeImageRegion

Synopsis
--------

This example demonstrates how to take advantage of MultiThreaderBase::ParallelizeImageRegion.
A comparison is made with LogImageFilter for purpose of computing log(1+x), where x is pixel value.

With ParallelizeImageRegion, we can process an image efficiently and in parallel
with a function that is defined in a flexible way. The entire operation, defined in 10 lines of code,
previously required the definition of an entire class.


Results
-------

Output::

  LogImageFilter and ParallelizeImageRegion generate the same result.


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::LogImageFilter
.. breathelink:: itk::MultiThreaderBase
