:name: MutualInformationAffine

Mutual Information Affine
=========================

.. index::
   single: AffineTransform
   single: MutualInformationImageToImageMetric
   single: GradientDescentOptimizer

.. toctree::
  :maxdepth: 1
   
  MutualInformationAffine.ipynb

Synopsis
--------

Global registration by maximizing the mutual information and using an affine transform.


Results
-------

.. figure:: fixed.png
  :alt: fixed.png

  Fixed

.. figure:: moving.png
  :alt: moving.png

  Moving

.. figure:: OutputBaseline.png
  :alt: OutputBaseline.png

  Output

Output::

  Optimizer stop condition: GradientDescentOptimizer: Maximum number of iterations (200) exceeded.
  Final Parameters: [1.0028069041777101, -0.009647107048100798, -0.010717116855425006, 1.0029040091646872, 13.26279335943067, 12.226979744206531]

  Result =
   Iterations    = 200
   Metric value  = 0.000971698
   Numb. Samples = 567

Jupyter Notebook
----------------

.. image:: https://mybinder.org/badge_logo.svg
  :target: https://mybinder.org/v2/gh/InsightSoftwareConsortium/ITKSphinxExamples/main?filepath=src%2FCore%2FTransform%2FMutualInformationAffine%2FMutualInformationAffine.ipynb


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
.. breathelink:: itk::GradientDescentOptimizer
