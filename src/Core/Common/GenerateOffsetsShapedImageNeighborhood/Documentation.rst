:name: GenerateOffsetsShapedImageNeighborhood

Generate the Offsets of a Shaped Image Neighborhood
===================================================

.. index::
   single: ConnectedImageNeighborhoodShape
   single: RectangularImageNeighborhoodShape
   single: ShapedImageNeighborhoodRange


Synopsis
--------


This example demonstrates various ways to create a container of offsets, to
specify the shape of a neighborhood of pixels:

 - An arbitrary shape
 - A 4-connected neighborhood shape
 - A rectangular neighborhood shape

These offsets may be used to specify the shape of a ShapedImageNeighborhoodRange
(as included with this code example), or a ShapedNeighborhoodIterator.

Results
-------

Output::

  Shape of some arbitrary offsets:

    [0, -1] [0, 1] [1, 1]

    0 0 0 0 0 0 0
    0 0 0 0 0 0 0
    0 0 0 1 0 0 0
    0 0 0 0 0 0 0
    0 0 0 2 3 0 0
    0 0 0 0 0 0 0
    0 0 0 0 0 0 0

  4-connected neighborhood shape (excluding the center pixel) with maximumCityblockDistance = 1:

    [0, -1] [-1, 0] [1, 0] [0, 1]

    0 0 0 0 0 0 0
    0 0 0 0 0 0 0
    0 0 0 1 0 0 0
    0 0 2 0 3 0 0
    0 0 0 4 0 0 0
    0 0 0 0 0 0 0
    0 0 0 0 0 0 0

  Rectangular shape of radius [1, 2]:

    [-1, -2] [0, -2] [1, -2] [-1, -1] [0, -1] [1, -1] [-1, 0] [0, 0] [1, 0] [-1, 1] [0, 1] [1, 1] [-1, 2] [0, 2] [1, 2]

    0 0 0 0 0 0 0
    0 0 1 2 3 0 0
    0 0 4 5 6 0 0
    0 0 7 8 9 0 0
    0 0 A B C 0 0
    0 0 D E F 0 0
    0 0 0 0 0 0 0


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ConnectedImageNeighborhoodShape itk::RectangularImageNeighborhoodShape
