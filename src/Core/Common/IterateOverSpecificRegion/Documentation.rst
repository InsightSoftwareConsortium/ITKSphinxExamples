:name: IterateOverSpecificRegion

Iterate Over Image While Skipping Specific Region
=================================================

.. index::
   single: ImageRegionExclusionConstIteratorWithIndex
   single: iterator
   pair: specific; region

Synopsis
--------

Iterator over an image skipping a specified region.


Results
-------
Output::

  0
  0
  0
  0
  0
  0
  Visited 6

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::ImageRegionExclusionConstIteratorWithIndex
