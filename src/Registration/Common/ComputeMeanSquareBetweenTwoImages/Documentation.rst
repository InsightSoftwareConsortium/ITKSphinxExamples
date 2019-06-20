Compute Mean Squares Metric Between Two Images
==============================================

.. index::
   single: MeanSquaresImageToImageMetric
   single: mean

Synopsis
--------

Compute the mean squares metric between two images.


Results
-------
Data from 2 images passed through
Output::

  [-10, -10]: 23101.7
  [-10, -5]: 23205.7
  [-10, 0]: 23260.4
  [-10, 5]: 23064.5
  [-10, 10]: 22914.5
  [-5, -10]: 23271.1
  [-5, -5]: 23351.3
  [-5, 0]: 23401
  [-5, 5]: 23185.1
  [-5, 10]: 23026.5
  [0, -10]: 23486.5
  [0, -5]: 23538.2
  [0, 0]: 23566.2
  [0, 5]: 23352.1
  [0, 10]: 23175.2
  [5, -10]: 23590.7
  [5, -5]: 23625.7
  [5, 0]: 23633.4
  [5, 5]: 23401.1
  [5, 10]: 23196.7
  [10, -10]: 23723.5
  [10, -5]: 23762.9
  [10, 0]: 23767.1
  [10, 5]: 23504.9
  [10, 10]: 23298.3


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MeanSquaresImageToImageMetric
