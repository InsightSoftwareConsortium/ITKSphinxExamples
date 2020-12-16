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
  :scale: 70%
  :alt: Input.png

  Yinyang.png

.. figure:: AddNoiseToBinaryImage.png
  :scale: 70%
  :alt: Output.png

  Output.png

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
