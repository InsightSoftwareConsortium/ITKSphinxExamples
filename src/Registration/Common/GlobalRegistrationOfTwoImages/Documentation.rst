Global Registration Of Two Images
=================================

.. index::
   single: ImageRegistrationMethod
   single: TranslationTransform

Synopsis
--------

A basic global registration of two images.


Results
-------
.. figure:: fixing.png
  :scale: 300%
  :alt: fixing.png generated image

  Fixed image.

.. figure:: moving.png
  :scale: 300%
  :alt: moving.png generated image

  Moving image.

.. figure:: output.png
  :scale: 300%
  :alt: output.png generated image

  Output image.

Output::

  Result =
  Translation X = 15.0103
  Translation Y = -1.12679
  Iterations    = 15
  Metric value  = 2374.3


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ImageRegistrationMethod
.. breathelink:: itk::TranslationTransform
