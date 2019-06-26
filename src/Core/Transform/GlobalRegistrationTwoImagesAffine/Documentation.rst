Global Registration Two Images (Affine)
=======================================

.. index::
   single: AffineTransform
   single: ImageRegistrationMethod
   single: affine

Synopsis
--------

A basic global registration of two images.


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

  Final parameters: [1.1921533496320087, 0.10372902569023787, -0.18132002016416124, 1.1464158834351523, 0.0021451859042650244, -0.003039195975788232]
  Result =
  Metric value  = 1836.41

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::AffineTransform
.. breathelink:: itk::ImageRegistrationMethod
