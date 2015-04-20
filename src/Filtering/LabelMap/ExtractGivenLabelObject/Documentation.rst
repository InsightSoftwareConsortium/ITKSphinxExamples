Extract Given Label Object
==========================

.. index::
   single: LabelSelectionLabelMapFilter

Synopsis
--------

Extract one given LabelObject from one LabelMap into a new LabelMap and remaining ones into another one.


Results
-------

.. figure:: 2th_cthead1.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: Output1Baseline.png
  :scale: 50%
  :alt: Output1 image

  first output (i.e. LabelMap with the LabelObject of interest)

.. figure:: Output2Baseline.png
  :scale: 50%
  :alt: Output2 image

  second output (i.e. LabelMap with remaining LabelObjects)


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::LabelSelectionLabelMapFilter
