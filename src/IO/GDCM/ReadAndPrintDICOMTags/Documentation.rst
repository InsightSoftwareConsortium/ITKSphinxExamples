 Read And Print DICOM Tags
================================

.. index::
   single: GDCMImageIO

Synopsis
--------


Example to read, search and print DICOM image metadata tags


Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :language: c++
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1,18-


Classes demonstrated
--------------------

.. breathelink:: itk::GDCMImageIO
