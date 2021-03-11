Apply Morphological Closing on All Label Objects
================================================

.. index::
   single: ObjectByObjectLabelMapFilter
   single: LabelUniqueLabelMapFilter

Synopsis
--------

Apply morphological closing operation on all LabelObjects of a given LabelMap.

In details:

* read image is converted to LabelMap
* apply morphological closing operation on all LabelObjects of the LabelMap
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

.. breathelink:: itk::LabelUniqueLabelMapFilter
