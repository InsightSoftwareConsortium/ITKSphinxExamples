Detect Edges With Canny Edge Detection Filter
=============================================

.. index::
  single: CannyEdgeDetectionImageFilter

Synopsis
--------

Apply CannyEdgeDetectionImageFilter to an image

Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Rescaled Output image

  Rescaled Output image (values are in [0, 255])

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 18-

Classes demonstrated
--------------------

.. breathelink:: itk::CannyEdgeDetectionImageFilter
