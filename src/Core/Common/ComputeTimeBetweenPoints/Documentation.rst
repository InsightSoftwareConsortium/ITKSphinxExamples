Compute Time Between Points
===========================

.. index::
   single: TimeProbe
   single: timer
   single: timing

Synopsis
--------


Compute the time between points in code. The `Report()` method is available in
ITK 4.9.0 or later.


Results
-------

Output::

  Mean: 0.00756311416626
  Total: 0.00756311416626
  Mean: 0.00671458244324
  Total: 0.0134291648865
  System:              clay
  Processor:           Unknown P6 family
      Cache:           15360
      Clock:           2194.87
      Cores:           12 cpus x 12 Cores = 144
      Virtual Memory:  Total: 0 Available: 0
      Physical Memory: Total:64294 Available: 36172
  OSName:              Linux
      Release:         4.1.4-calculate
      Version:         #2 SMP PREEMPT Sun Aug 9 17:03:44 EDT 2015
      Platform:        x86_64
      Operating System is 64 bit
  ITK Version: 4.9.0
  Name Of Probe(Time)           Iteration      Total(s)       Min(s)         Mean(s)        Max(s)         Std(s)
                                2              0.0134292      0.00586605     0.00671458     0.00756311     0.00120001

Code
----

C++
...

.. literalinclude:: Code.cxx
   :language: c++
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::TimeProbe
