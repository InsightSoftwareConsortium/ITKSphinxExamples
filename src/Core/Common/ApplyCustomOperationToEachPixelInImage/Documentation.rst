:name: ApplyCustomOperationToEachPixelInImage

Apply Custom Operation to Each Pixel in Image
=============================================

.. index::
   single: UnaryFunctorImageFilter

Synopsis
--------
Apply a custom operation to each pixel in an image.

.. figure:: Relationship.png
  :scale: 70%
  :alt: Relationship.png


.. figure:: Operation.png
  :scale: 70%
  :alt: Operation.png

pixel-wise operation on 2D vector image.

Results
-------
Output::

  pixel (1,1) was = [1,0]
  pixel (1,1) now = [-4.37144e-08, 1]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::UnaryFunctorImageFilter
