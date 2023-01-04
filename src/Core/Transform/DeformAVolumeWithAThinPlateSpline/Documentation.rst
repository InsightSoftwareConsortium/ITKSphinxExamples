:name: DeformAVolumeWithAThinPlateSpline

Deform a Volume With a Thin Plate Spline
========================================

.. index::
   single: ThinPlateSplineKernelTransform

Synopsis
--------


This example deforms a 3D volume with the thin plate spline.


Results
-------

.. figure:: InputImage.png
  :width: 640px
  :alt: Input image

  Input image

.. figure:: DeformedImage.png
  :width: 640px
  :alt: Deformed image

  Deformed image

.. figure:: CheckerBoard.png
  :width: 640px
  :alt: CheckerBoard image

  CheckerBoard image

Code
----

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1,16-

C++
...

.. literalinclude:: Code.cxx
   :language: c++
   :lines: 18-



Classes demonstrated
--------------------

.. breathelink:: itk::ThinPlateSplineKernelTransform
