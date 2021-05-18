:name: MaskOneImageGivenLabelMap

Mask One Image Given Label Map
==============================

.. index::
   single: LabelMapMaskImageFilter

Synopsis
--------

Mask the content of one input itk::Image according to one input itk::LabelMap


Results
-------

.. figure:: cthead1.png
  :scale: 100%
  :alt: Input image

  Input image

.. figure:: 2th_cthead1.png
  :scale: 100%
  :alt: Input label image

  Input label image

.. figure:: Output1Baseline.png
  :scale: 100%
  :alt: Masked output 1

  Masked output with label 100, background 0.

.. figure:: Output2Baseline.png
  :scale: 100%
  :alt: Masked output 2

  Masked output with label 0, background 0, negated, cropped, and border size
  10.


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::LabelMapMaskImageFilter
