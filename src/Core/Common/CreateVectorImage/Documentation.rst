:name: CreateVectorImage

Create Vector Image
===================

.. index::
   single: VectorImage

Synopsis
--------

Create a vector image.

.. figure:: Operation.png
  :scale: 70%
  :alt: operation.png

How the image whose pixels are of vector type can be set using a VariableLengthVector at runtime

Results
-------
Output::

  pixel (1,1) = [0, 0]
  pixel (1,1) = [1.1, 2.2]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::VectorImage
