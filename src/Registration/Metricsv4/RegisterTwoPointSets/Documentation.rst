:name: RegisterTwoPointSets

Register Two Point Sets
=======================

Index
--------
.. index::
   single: JensenHavrdaCharvatTsallisPointSetToPointSetMetricv4
   single: GradientDescentOptimizerv4
   single: RegistrationParameterScalesFromPhysicalShift
   single: AffineTransform
   single: PointSet

.. seealso:: registration; transformation; pointset

.. toctree::
  :maxdepth: 1
   
  RegisterTwoPointSets.ipynb

Synopsis
--------

Register two point sets with the Jensen-Havrda-Charvat-Tsallis point set
metric.

Results
--------

::

  It: 0    metric value: -0.0641355
  It: 1    metric value: -0.0955508
  It: 2    metric value: -0.0956365
  It: 3    metric value: -0.0956648
  It: 4    metric value: -0.0956742
  It: 5    metric value: -0.0956774
  It: 6    metric value: -0.0956784
  It: 7    metric value: -0.0956788
  It: 8    metric value: -0.0956789
  It: 9    metric value: -0.0956789
  numberOfIterations: 10
  Moving-source final value: -0.0956789
  Moving-source final position: [0.9999999481711049, 3.6956646020565954e-9,
                                 -3.9958144654776e-8, 1.0000000021678688,
                                 1.9991709056354183, 1.999169080146488]
  Optimizer scales: [10000, 9998.46502472856,
                     10000, 9998.46502472848,
                     1.0000000000010232, 1.0000000000010232]
  Optimizer learning rate: 164.938

Jupyter Notebook
----------------

.. image:: https://mybinder.org/badge_logo.svg
  :target: https://mybinder.org/v2/gh/InsightSoftwareConsortium/ITKSphinxExamples/main?filepath=src%2FRegistration%2FMetricsv4%2FRegisterTwoPointSets%2FRegisterTwoPointSets.ipynb

Code
--------

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 23-

C++
...

.. literalinclude:: Code.cxx
   :lines: 20-

Classes demonstrated
--------------------

.. breathelink:: itk::JensenHavrdaCharvatTsallisPointSetToPointSetMetricv4
.. breathelink:: itk::GradientDescentOptimizerv4Template
