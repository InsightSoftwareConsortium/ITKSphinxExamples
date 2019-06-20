Add Noise To Binary Image
=========================

.. index::
   single: ImageRandomNonRepeatingIteratorWithIndex
   single: noise
   pair: binary; image

Synopsis
--------

Add noise to a binary image.


Results
-------
.. figure:: Yinyang.png
  :scale: 60%
  :alt: Input.png

  Input image.

.. figure:: AddNoiseToBinaryImage.png
  :scale: 60%
  :alt: Output.png

  Output image.
Output::

  Number of random samples: 105062

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ImageRandomNonRepeatingIteratorWithIndex
