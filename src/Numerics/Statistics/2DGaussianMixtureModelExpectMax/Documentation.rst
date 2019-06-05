2D Gaussian Mixture Model Expectation Maximum
=============================================

.. index::
   single: ExpectationMaximizationMixtureModelEstimator
   single: max
   pair: 2D; gaussian

Synopsis
--------

2D Gaussian Mixture Model Expectation Maximization.


Results
-------
Output::
  Cluster[0]
      Parameters:
           [101.40933830302448, 99.43004497807948, 1098.5993639665169, -107.16526601343287, -107.16526601343287, 913.9641556669595]
      Proportion:          0.495716
  Cluster[1]
      Parameters:
           [196.3354813961237, 195.29542020949035, 991.7367739288584, 84.51759523418217, 84.51759523418217, 845.9604643808337]
      Proportion:          0.504284
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

.. breathelink:: itk::ExpectationMaximizationMixtureModelEstimator
