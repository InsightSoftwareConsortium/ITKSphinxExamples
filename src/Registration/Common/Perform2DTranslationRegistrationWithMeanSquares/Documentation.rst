Perform 2D Translation Registration With Mean Squares
=====================================================

.. index::
   single: ImageRegistrationMethodv4, TranslationTransform
   single: ImageRegistrationMethodv4, MeanSquaresImageToImageMetricv4
   single: ImageRegistrationMethodv4, RegularStepGradientDescentOptimizerv4

Synopsis
--------

This example illustrates the use of the image registration framework in
Insight.  It should be read as a ``Hello World`` for ITK registration.
Instead of means to an end, this example should be read as a basic
introduction to the elements typically involved when solving a problem
of image registration.

A registration method requires the following set of components: two input
images, a transform, a metric and an optimizer. Some of these components
are parameterized by the image type for which the registration is intended.
The following header files provide declarations of common types used for
these components.

This example corresponds to the ImageRegistration1.cxx example from
the ITK software guide.

Results
-------

.. |input1| image:: BrainProtonDensitySliceBorder20.png
  :alt: Input images

.. |input2| image:: BrainProtonDensitySliceShifted13x17y.png
  :alt: Input images

+----------+----------+
| |input1| | |input2| |
+----------+----------+

  Input images (fixed image left/ moving image right).

.. figure:: OutputBaseline.png
  :alt: Output image

  Output registered image.

.. |diff1| image:: ImageRegistration1DifferenceBefore.png
  :alt: Image difference before registration.

.. |diff2| image:: ImageRegistration1DifferenceAfter.png
  :alt: Image difference after registration.

+---------+---------+
| |diff1| | |diff2| |
+---------+---------+

  Image difference between moving and fixed image (left before registration, right after registration).

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageRegistrationMethodv4
