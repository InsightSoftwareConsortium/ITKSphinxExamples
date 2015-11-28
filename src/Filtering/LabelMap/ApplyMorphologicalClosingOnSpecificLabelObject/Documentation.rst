Apply Morphological Closing On Specific Label Object
====================================================

.. index::
   single: LabelSelectionLabelMapFilter
   single: ObjectByObjectLabelMapFilter
   single  MergeLabelMapFilter
   single: LabelUniqueLabelMapFilter

Synopsis
--------

Apply BinaryMorphologicalClosingFilter on one LabelObject of given LabelMap.

In details:

* read one Image
* convert the LabelImage into one LabelMap
* extract the LabelObject of interest using LabelSelectionLabelMapFilter
* apply morphological closing operation on the LabelObject of interest
* merge the processed LabelObject with remaining LabelObjects from LabelSelectionLabelMapFilter
* make sure there is no overlapping LabelObject with using LabelUniqueLabelMapFilter
* convert the LabelMap to LabelImage
* write the corresponding LabelImage

Results
-------

.. figure:: 2th_cthead1.png
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
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ObjectByObjectLabelMapFilter
