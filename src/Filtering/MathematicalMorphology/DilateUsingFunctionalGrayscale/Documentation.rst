:name: DilateUsingFunctionalGrayscale

Dilate a grayscale image using a functional kernel
===================================================

.. index::
  single: BinaryBallStructuringElement
  single: GrayscaleFunctionDilateImageFilter
  pair: mathematical morphology; dilation

.. seealso:: dilation; erosion


Synopsis
--------

Dilate an image using functional grayscale morphology.
Function dilation takes the maximum of all the pixels identified by the structuring element plus the structuring element value.
In this example, the white regions are enlarged.



Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input ct head image.

  Input grayscale image.

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Dilated output.

  Dilated output.


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

.. breathelink:: itk::GrayscaleFunctionDilateImageFilter itk::BinaryBallStructuringElement
