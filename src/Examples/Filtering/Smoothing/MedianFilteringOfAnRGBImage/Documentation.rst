Median Filtering Of An RGB Image
================================

.. index::
   single: MedianImageFilter

Synopsis
--------


Apply median filtering on a RGB Image. The sorting of pixel is performed on their luminance.


Results
-------

.. figure:: GourdsRGB.png
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::MedianImageFilter
