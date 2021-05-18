:name: ExtractChannelOfImageWithMultipleComponents

Extract Channel of Image With Multiple Components
=================================================

.. index::
   single: NthElementImageAdaptor
   single: itkimage
   pair: extract; channel

Synopsis
--------

Extract a component/channel of an itkImage with pixels with multiple components.


Results
-------

Output::

  [1, 2, 3]
  1


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::NthElementImageAdaptor
