Process A 2D Slice Of A 3D Image
================================

.. index::
   single: ExtractImageFilter

Synopsis
--------

This example illustrates the common task of extracting a 2D slice from a
3D volume. Perform some processing on that slice and then paste it on an
output volume of the same size as the volume from the input.


Results
-------

.. figure::Input232.png
  :scale: 50%
  :alt: Slice of input

  Slice of input

.. figure::Output232.png
  :scale: 50%
  :alt: Slice of output

  Slice of output


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
   :lines: 1, 16-


Classes demonstrated
--------------------

.. breathelink:: itk::ExtractImageFilter
.. breathelink:: itk::PasteImageFilter
.. breathelink:: itk::MedianImageFilter
