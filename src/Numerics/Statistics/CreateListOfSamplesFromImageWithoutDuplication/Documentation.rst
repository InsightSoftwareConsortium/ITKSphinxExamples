:name: CreateListOfSamplesFromImageWithoutDuplication

Create List of Samples From Image Without Duplication
=====================================================

.. index::
   single: ImageToListSampleAdaptor
   pair: without; duplication

Synopsis
--------

Create a list of samples from an image without duplicating the data.


Results
-------
Output::

  [96.6165]
  [833.994]
  [935.002]
  [571.885]
  [663.087]
  [496.426]
  [429.681]
  [649.809]
  [333.22]
  [425.118]
  [965.227]
  [568.819]
  [133.191]
  [547.472]
  [361.405]
  [136.599]
  [823.276]
  [802.849]
  [475.275]
  [947.74]
  [96.6244]
  [965.532]
  [690.606]
  [13.2403]
  [529.497]
  [258.332]
  [780.933]
  [135.776]
  [985.543]
  [23.581]
  [325.735]
  [623.222]
  [485.055]
  ...

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::Statistics::ImageToListSampleAdaptor
