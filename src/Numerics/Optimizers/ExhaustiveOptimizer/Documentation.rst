Exhaustive Optimizer
====================

.. index::
   single: ExhaustiveOptimizer

Synopsis
--------

An optimizer that fully samples a grid on the parametric space.


Results
-------
Results from 1 fixedImage and 1 movingImage
Output::

  Iteration: 0   [0, 0, 0]   24601.8   [-3.141592653589793, 64, 69]
  Iteration: 1   [1, 0, 0]   22112.4   [-2.617993877991494, 64, 69]
  Iteration: 2   [2, 0, 0]   21066.7   [-2.0943951023931953, 64, 69]
  Iteration: 3   [3, 0, 0]   21944.1   [-1.5707963267948966, 64, 69]
  Iteration: 4   [4, 0, 0]   23625   [-1.0471975511965976, 64, 69]
  Iteration: 5   [5, 0, 0]   23355.7   [-0.5235987755982988, 64, 69]
  Iteration: 6   [6, 0, 0]   22546.6   [0, 64, 69]
  Iteration: 7   [7, 0, 0]   20374   [0.5235987755982988, 64, 69]
  Iteration: 8   [8, 0, 0]   20294.5   [1.0471975511965976, 64, 69]
  Iteration: 9   [9, 0, 0]   22787.5   [1.5707963267948966, 64, 69]
  Iteration: 10   [10, 0, 0]   25424.1   [2.0943951023931953, 64, 69]
  Iteration: 11   [11, 0, 0]   25393.6   [2.617993877991494, 64, 69]
  Iteration: 12   [12, 0, 0]   24601.8   [3.141592653589793, 64, 69]
  MinimumMetricValue: 20294.5
  MaximumMetricValue: 25424.1
  MinimumMetricValuePosition: [1.0471975511965976, 64, 69]
  MaximumMetricValuePosition: [2.0943951023931953, 64, 69]


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ExhaustiveOptimizer
