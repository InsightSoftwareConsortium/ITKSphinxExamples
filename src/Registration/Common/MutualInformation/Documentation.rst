Mutual Information
==================

.. index::
   single: MutualInformationImageToImageMetric
   single: TranslationTransform

Synopsis
--------

Global registration by maximizing the mutual information and using a translation only transform.


Results
-------
.. figure:: fixed.png
  :scale: 70%
  :alt: fixed.png

  fixed.png

.. figure:: moving.png
  :scale: 70%
  :alt: moving.png

  moving.png

.. figure:: output.png
  :scale: 70%
  :alt: output.png

  output.png

Output::

  Optimizer stop condition: GradientDescentOptimizer: Maximum number of iterations (200) exceeded.

  Result =
  Translation X = -5.58344
  Translation Y = -0.129678
  Iterations    = 200
  Metric value  = -0.00067634
  Numb. Samples = 100

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MutualInformationImageToImageMetric
.. breathelink:: itk::TranslationTransform
