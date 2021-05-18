:name: SmoothImageWhilePreservingEdges

Smooth Image While Preserving Edges
===================================

.. index::
   single: VectorGradientAnisotropicDiffusionImageFilter
   single: smooth

Synopsis
--------

Smooth an image while preserving edges.


Results
-------
.. figure:: Yinyang.png
  :scale: 70%

  Input image.

.. figure:: SmoothImageWhilePreservingEdges.png
  :scale: 70%

  Output In VTK Window

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::VectorGradientAnisotropicDiffusionImageFilter
