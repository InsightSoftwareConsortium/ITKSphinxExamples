Scale All Pixel's Sum To Constant
=================================

.. index::
   single: NormalizeToConstantImageFilter
   pair: pixel; constant

Synopsis
--------

Scale all pixels so that their sum is a specified constant.


Results
-------
Output::

  0.111111
  0.111111
  0.111111
  0.111111
  0.111111
  0.111111
  0.111111
  0.111111
  0.111111


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::NormalizeToConstantImageFilter
