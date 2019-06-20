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
  :scale: 300%
  :alt: fixed.png image generated

  Fixed image.

.. figure:: moving.png
  :scale: 300%
  :alt: moving.png image generated

  Moving image.

.. figure:: output.png image generated
  :scale: 300%
  :alt: output.png

  Output image.

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
