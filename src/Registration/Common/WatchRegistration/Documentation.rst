Watch Registration
==================

.. index::
   single: MattesMutualInformationImageToImageMetric

Synopsis
--------

Watch the iterations of a registration using VTK.


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

.. figure:: WatchRegistration.png
  :scale: 70%
  :alt: VTK Window

  Output In VTK Window

Output::

  Optimizer stop condition: RegularStepGradientDescentOptimizer: Maximum number of iterations (1000) exceeded.
  Final Transform: AffineTransform (0x7f9129d00120)
  RTTI typeinfo:   itk::AffineTransform<double, 2u>
  Reference Count: 4
  Modified Time: 215110
  Debug: Off
  Object Name:
  Observers:
    none
  Matrix:
    0.789218 0.062097
    0.139299 0.37936
  Offset: [7.3411, 26.2747]
  Center: [49.5, 49.5]
  Translation: [-0.0188083, 2.44832]
  Inverse:
    1.30477 -0.213577
    -0.479108 2.71444
  Singular: 0

  Final Parameters: [0.7892180100803599, 0.06209699937125816, 0.13929938284463836, 0.37935986885403217, -0.018808339095318795, 2.448323274873905]

  Result =
  Iterations    = 1000
  Metric value  = -0.00195192
  Numb. Samples = 500


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::MattesMutualInformationImageToImageMetric
