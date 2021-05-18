:name: GlobalRegistrationOfTwoImages

Global Registration of Two Images
=================================

.. index::
   single: ImageRegistrationMethod
   single: TranslationTransform

Synopsis
--------

A basic global registration of two images.


Results
-------
.. figure:: fixed.png
  :scale: 70%
  :alt: fixing.png

  fixing.png

.. figure:: moving.png
  :scale: 70%
  :alt: moving.png

  moving.png

.. figure:: output.png
  :scale: 70%
  :alt: output.png

  output.png

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
