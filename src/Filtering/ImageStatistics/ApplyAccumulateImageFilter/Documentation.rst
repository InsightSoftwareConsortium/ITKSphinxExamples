Apply Accumulate Image Filter
=============================

.. index::
   single: AccumulateImageFilter

Synopsis
--------

Accumulate pixels of an image along a selected direction.


Results
-------

.. figure:: Input.png
  :scale: 100%
  :alt: Input image

  Input image

.. figure:: Output0.png
  :scale: 100%
  :alt: Output image 0

  Output image accumulated along direction 0

.. figure:: Output1.png
  :scale: 100%
  :alt: Output image 1

  Output image accumulated along direction 1

.. figure:: Output2.png
  :scale: 100%
  :alt: Output image 2

  Output image accumulated along direction 2


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::AccumulateImageFilter
