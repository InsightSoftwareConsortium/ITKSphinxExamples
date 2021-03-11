Create Histogram From List of Measurements
==========================================

.. index::
   single: SampleToHistogramFilter
   single: histogram

Synopsis
--------

Create a histogram from a list of sample measurements.


Results
-------
Output::

  Histogram vector size: 1
  Frequency of 0 : (1 to 1.1001) = 2
  Frequency of 1 : (1.1001 to 1.2002) = 0
  Frequency of 2 : (1.2002 to 1.3003) = 0
  Frequency of 3 : (1.3003 to 1.4004) = 0
  Frequency of 4 : (1.4004 to 1.5005) = 0
  Frequency of 5 : (1.5005 to 1.6006) = 0
  Frequency of 6 : (1.6006 to 1.7007) = 0
  Frequency of 7 : (1.7007 to 1.8008) = 0
  Frequency of 8 : (1.8008 to 1.9009) = 0
  Frequency of 9 : (1.9009 to 2.001) = 1
  Total count 3

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::Statistics::SampleToHistogramFilter
