:name: MiniPipeline

Mini Pipeline
=============

.. index::
   single: Image

Synopsis
--------

Mini Pipeline.

.. figure:: MiniPipeline.png
  :scale: 70%
  :alt: MiniPipeline.png

Example of a typical mini pipeline or composite filter that can encapsulate a number of other filters.

Results
-------
Output::

  Input:
  ImageRegion (0x7fe4c3aaadb0)
  Dimension: 2
  Index: [0, 0]
  Size: [200, 300]

  Input:
  ImageRegion (0x7fe4c3aab920)
  Dimension: 2
  Index: [0, 0]
  Size: [200, 300]

.. figure:: MiniPipelineOutput.png
  :scale: 70%
  :alt: Output.png

  Output.png


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::Image
