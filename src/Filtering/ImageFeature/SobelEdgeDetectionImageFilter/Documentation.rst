:name: SobelEdgeDetectionImageFilter

Sobel Edge Detection Image Filter
==================================

.. index::
  single: SobelEdgeDetectionImageFilter

Synopsis
--------

Apply SobelEdgeDetectionImageFilter to an image

Results
-------

.. figure:: Gourds.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: SobelEdgeDetectionImageFilterRescaledOutputBaseline.png
  :scale: 50%
  :alt: Rescaled Output image

  Rescaled Output image (values are in [0, 255])

Code
----

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::SobelEdgeDetectionImageFilter
