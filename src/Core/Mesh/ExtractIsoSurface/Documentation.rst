:name: ExtractIsoSurface

Extract Iso Surface
===================

.. index::
   single: BinaryMask3DMeshSource

Synopsis
--------

Extract the iso surface as one itk::Mesh from a 3D itk::Image


Results
-------

.. figure:: MeshAndVolume.png
  :scale: 50%
  :alt: Input image and resulting mesh

  Input 3D image with iso-surface mesh

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::BinaryMask3DMeshSource
