Median Filtering Of An Image
============================

.. index::
   single: MedianImageFilter
   single: smooth

Synopsis
--------

Apply median filtering on an image.


Results
-------

.. figure:: Gourds.png
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :alt: Output image

  Output image


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

.. breathelink:: itk::MedianImageFilter
