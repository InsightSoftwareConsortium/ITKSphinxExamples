Overlay Label Map On Top Of An Image
====================================

.. index::
   single: LabelMapOverlayImageFilter

Synopsis
--------

Apply a colormap to a label map and superimpose it on an image


Results
-------

.. figure:: Gourds.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: label.png
  :scale: 50%
  :alt: Label map

  Label image

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

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::LabelMapOverlayImageFilter
