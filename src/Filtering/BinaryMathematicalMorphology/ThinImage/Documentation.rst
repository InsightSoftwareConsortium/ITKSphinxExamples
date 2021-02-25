:name: ThinImage

Thin Image
==========

.. index::
   single: BinaryThinningImageFilter

Synopsis
--------

Skeletonix/thin an image.


Results
-------
.. figure:: Input.png
  :scale: 70%
  :alt: Input.png

  input.png

.. figure:: OutputBaseline.png
  :scale: 70%
  :alt: OutputBaseline.png

  OutputBaseline.png

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

.. breathelink:: itk::BinaryThinningImageFilter
