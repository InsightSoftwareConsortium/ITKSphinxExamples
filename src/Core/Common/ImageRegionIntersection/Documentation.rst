:name: ImageRegionIntersection

Image Region Intersection
=========================

.. index::
   single: ImageRegion
   pair: ImageRegion; IsInside

Synopsis
--------


This example demonstrates how to check if two regions of an image overlap/intersect.

.. figure:: ImageRegionIntersection.png
  :scale: 70%
  :alt: imageregionintersection.png



Results
-------

Output::

  Small inside region is 1
  Small outside region is 0
  Small overlap region is 0

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageRegion
