Register Image To Another Using Landmarks
=========================================

.. index::
   single: LandmarkBasedTransformInitializer
   single: landmark

Synopsis
--------

Rigidly register one image to another using manually specified landmarks.


Results
-------
.. figure:: fixing.png
  :scale: 300%
  :alt: fixed.png image generated

  Fixed image.

.. figure:: moving.png
  :scale: 300%
  :alt: moving.png image generated

  Moving image.

.. figure:: output.png
  :scale: 300%
  :alt: output.png image generated

  Output image.

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::LandmarkBasedTransformInitializer
