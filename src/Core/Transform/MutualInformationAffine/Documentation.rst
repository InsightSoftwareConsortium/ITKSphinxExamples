Mutual Information Affine
=========================

.. index::
   single: AffineTransform
   single: MutualInformationImageToImageMetric

Synopsis
--------

Global registration by maximizing the mutual information and using an affine transform.


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

  Optimizer stop condition: GradientDescentOptimizer: Maximum number of iterations (1000) exceeded.
  Final Parameters: [2.03502150081667, 0.4815329593844025, -0.524998748481682, 0.5494736862921054, 0.016827072908497744, -0.018211282766070345]
  Result =
   Iterations    = 1000
   Metric value  = -0.000162484
   Numb. Samples = 100

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::AffineTransform
.. breathelink:: itk::MutualInformationImageToImageMetric
