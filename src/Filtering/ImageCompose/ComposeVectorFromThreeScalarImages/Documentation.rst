:name: ComposeVectorFromThreeScalarImages

Compose Vector From Three Scalar Images
=======================================

.. index::
   single: ComposeImageFilter
   pair: vector; image

Synopsis
--------

Compose a vector image (with 3 components) from three scalar images.


Results
-------
Output::

  1.2
  [1.2, 1.2, 1.2]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ComposeImageFilter
