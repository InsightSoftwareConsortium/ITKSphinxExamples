:name: ReadAPointSet

Read a PointSet
===============

.. index::  single: PointSet
            single: Mesh
            single: VTKPolyDataReader
            pair: Mesh; GetPoint


Synopsis
--------

Read a PointSet


Results
-------
.. figure:: tetrahedron.png
  :scale: 70%
  :alt: InputVTK.png

Print all points

.. raw:: html

  <div class="figure">
    <iframe src="XTKViewer.html" width="400" height="450" seamless></iframe>
    <p class="caption">Interactive input mesh</p>
  </div>


Output::

   Input file: tetrahedron.vtk
   Testing itk::VTKPolyDataReader
   numberOfPoints= 4
   numberOfCells= 4
   Point is = [0.5, 0, 0]
   Point is = [-0.5, 0.5, 0]
   Point is = [-0.5, -0.25, 0.433013]
   Point is = [-0.5, -0.25, -0.433013]

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

WebAssembly
......

.. literalinclude:: WebAssembly.html
   :language: html
   :lines: 1, 20-


Classes demonstrated
--------------------

.. breathelink:: itk::PointSet
