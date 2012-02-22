Add Offset To Index
===================

.. index::
   single: Offset
   single: Index

Synopsis
--------


Add an offset to a pixel index


Results
-------

Output::
  index: [5, 5]
  offset: [1, 1]
  index + offset: [6, 6]

  index: [5, 5]
  offset: [-1, 1]
  index + offset: [4, 6]


Code
----

C++
...

.. literalinclude:: AddOffsetToIndex.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::Offset itk::Index
