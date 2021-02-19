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

.. figure:: OutputBaseline.png
  :scale: 70%
  :alt: OutputBaseline.png

  OutputBaseline.png

Output::

  Optimizer stop condition: GradientDescentOptimizer: Maximum number of iterations (200) exceeded.
 
    Result =
     Translation X = 12.9484
     Translation Y = 17.0856
     Iterations    = 200
     Metric value  = 0.594482
     Numb. Samples = 567

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Binder
------
.. image:: https://mybinder.org/badge_logo.svg
 :target: https://mybinder.org/v2/gh/InsightSoftwareConsortium/ITKExamples/master?filepath=src%2FRegistration%2FCommon%2FMutualInformation%2FMutualInformation.ipynb



Classes demonstrated
--------------------

.. breathelink:: itk::MutualInformationImageToImageMetric
.. breathelink:: itk::TranslationTransform
