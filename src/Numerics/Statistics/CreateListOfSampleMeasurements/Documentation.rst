Create List of Sample Measurements
==================================

.. index::
   single: ListSample

Synopsis
--------

Create a lsit of sample measurements.


Results
-------
Output::

  id = 0	 measurement vector = [1, 2, 4]	 frequency = 1
  id = 1	 measurement vector = [2, 4, 5]	 frequency = 1
  id = 2	 measurement vector = [3, 8, 6]	 frequency = 1
  id = 0	 measurement vector = [1, 2, 4]	 frequency = 1
  id = 1	 measurement vector = [2, 4, 5]	 frequency = 1
  id = 2	 measurement vector = [3, 8, 6]	 frequency = 1
  Size = 3
  Total frequency = 3

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::Statistics::ListSample
