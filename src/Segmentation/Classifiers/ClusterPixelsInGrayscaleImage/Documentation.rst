Cluster Pixels In Grayscale Image
=================================

.. index::
   single: ScalarImageKmeansImageFilter
   pair: grayscale; image

Synopsis
--------

Cluster the pixels in a greyscale image.


Results
-------
.. figure:: ClusterPixelsInGrayscaleImage.png
  :scale: 70%
  :alt: VTK Window

  Output In VTK Window

Output::

  cluster[0]     estimated mean : 10
  cluster[1]     estimated mean : 100
  cluster[2]     estimated mean : 200
  Number of pixels per class


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ScalarImageKmeansImageFilter
