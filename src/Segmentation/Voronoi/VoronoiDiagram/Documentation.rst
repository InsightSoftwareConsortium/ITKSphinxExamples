:name: VoronoiDiagram

Voronoi Diagram
===============

.. index::
   single: VoronoiDiagram2D
   single: VoronoiDiagram2DGenerator

Synopsis
--------

Voronoi diagram.


Results
-------
.. warning::
  **Fix Errors**
  Example contains errors needed to be fixed for proper output.

Output::

  Seed No.0: At (25,25)
  Boundary Vertices List (in order):4,8,7,0,1,
  Neighbors (Seed No.):2,3,1,

  Seed No.1: At (75,25)
  Boundary Vertices List (in order):6,11,7,0,2,
  Neighbors (Seed No.):2,4,0,

  Seed No.2: At (50,50)
  Boundary Vertices List (in order):2,0,1,3,
  Neighbors (Seed No.):0,1,3,4,

  Seed No.3: At (25,75)
  Boundary Vertices List (in order):5,9,4,1,3,
  Neighbors (Seed No.):2,0,4,

  Seed No.4: At (75,75)
  Boundary Vertices List (in order):5,10,6,2,3,
  Neighbors (Seed No.):2,3,1,

  Vertices Informations:
  Vertices No.0: At (50,25)
  Vertices No.1: At (25,50)
  Vertices No.2: At (75,50)
  Vertices No.3: At (50,75)
  Vertices No.4: At (0,50)
  Vertices No.5: At (50,100)
  Vertices No.6: At (100,50)
  Vertices No.7: At (50,0)
  Vertices No.8: At (0,0)
  Vertices No.9: At (0,100)
  Vertices No.10: At (100,100)
  Vertices No.11: At (100,0)
  IIBI-SYNAPSE006:bin mseng$ ./VoronoiDiagram
  Seed No.0: At (25,25)
  Boundary Vertices List (in order):4,8,7,0,1,
  Neighbors (Seed No.):2,3,1,

  Seed No.1: At (75,25)
  Boundary Vertices List (in order):6,11,7,0,2,
  Neighbors (Seed No.):2,4,0,

  Seed No.2: At (50,50)
  Boundary Vertices List (in order):2,0,1,3,
  Neighbors (Seed No.):0,1,3,4,

  Seed No.3: At (25,75)
  Boundary Vertices List (in order):5,9,4,1,3,
  Neighbors (Seed No.):2,0,4,

  Seed No.4: At (75,75)
  Boundary Vertices List (in order):5,10,6,2,3,
  Neighbors (Seed No.):2,3,1,

  Vertices Informations:
  Vertices No.0: At (50,25)
  Vertices No.1: At (25,50)
  Vertices No.2: At (75,50)
  Vertices No.3: At (50,75)
  Vertices No.4: At (0,50)
  Vertices No.5: At (50,100)
  Vertices No.6: At (100,50)
  Vertices No.7: At (50,0)
  Vertices No.8: At (0,0)
  Vertices No.9: At (0,100)
  Vertices No.10: At (100,100)
  Vertices No.11: At (100,0)

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::VoronoiDiagram2D
.. breathelink:: itk::VoronoiDiagram2DGenerator
