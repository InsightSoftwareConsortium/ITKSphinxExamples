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
.. figure:: fixed.png
  :scale: 70%
  :alt: fixed.png

  fixed.png

.. figure:: moving.png
  :scale: 70%
  :alt: moving.png

  moving.png

.. figure:: output.png
  :scale: 70%
  :alt: output.png

  output.png

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::LandmarkBasedTransformInitializer
