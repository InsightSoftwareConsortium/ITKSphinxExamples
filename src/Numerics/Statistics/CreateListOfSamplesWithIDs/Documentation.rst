Create List Of Samples With Associated ID's
===========================================

.. index::
   single: MembershipSample

Synopsis
--------

Create a list of samples with associated class IDs.


Results
-------
Output::
  instance identifier = 0	 measurement vector = [1, 2, 4]	 frequency = 1	 class label = 0
  instance identifier = 1	 measurement vector = [2, 4, 5]	 frequency = 1	 class label = 0
  instance identifier = 2	 measurement vector = [3, 8, 6]	 frequency = 1	 class label = 1
  instance identifier = 0	 measurement vector = [1, 2, 4]	 frequency = 1
  instance identifier = 1	 measurement vector = [2, 4, 5]	 frequency = 1

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::MembershipSample
