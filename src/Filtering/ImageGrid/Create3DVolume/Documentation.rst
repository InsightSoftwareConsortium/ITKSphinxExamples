Create 3D Volume
================

.. index::
   single: TileImageFilter
   single: append
   single: tile
   single: concatenate

Synopsis
--------

This example reads in a series of 2D images and stacks them to create a 3D image.

Results
-------

.. figure:: Input.png
  :scale: 50%
  :alt: Input 2D images

  Input 2D images

.. figure:: Output.png
  :scale: 80%
  :alt: Output 3D image

  Single output 3D image


Code
----

C++
...

.. literalinclude:: Code.cxx

Python
......

.. literalinclude:: Create3DVolume.py


Classes demonstrated
--------------------

.. breathelink:: itk::TileImageFilter
