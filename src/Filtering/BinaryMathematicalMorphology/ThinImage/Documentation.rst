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
.. figure:: input.png
  :scale: 70%
  :alt: input.png

  input.png

.. figure:: output.png
  :scale: 70%
  :alt: output.png

  output.png

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
