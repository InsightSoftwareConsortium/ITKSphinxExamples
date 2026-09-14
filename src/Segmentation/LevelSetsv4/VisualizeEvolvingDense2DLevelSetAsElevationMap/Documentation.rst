:name: VisualizeEvolvingDense2DLevelSetAsElevationMap

Visualize an Evolving Dense 2D Level Set as Elevation Map
=========================================================

.. index::
   single: VTKVisualize2DLevelSetAsElevationMap
   single: BinaryImageToLevelSetImageAdaptor
   single: SinRegularizedHeavisideStepFunction
   single: LevelSetDenseImage
   single: LevelSetContainer
   single: LevelSetEquationChanAndVeseInternalTerm
   single: LevelSetEquationChanAndVeseExternalTerm
   single: LevelSetEvolutionNumberOfIterationsStoppingCriterion
   single: LevelSetEvolution
   single: LevelSetIterationUpdateCommand


Synopsis
--------

Visualize an evolving dense level-set function 2D rendered as an elevation map.


Results
-------

.. figure:: cells.png
  :scale: 100%
  :alt: Input image (cells)

  Input image

.. figure:: levelsets.*
  :scale: 100%
  :alt: Evolving level-sets rendered as an elevation map

  Evolving level-sets

.. only:: html

  .. image:: levelsets.gif
    :scale: 100%
    :alt: Evolving level-sets animation


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. [breathelink:: itk::VTKVisualize2DLevelSetAsElevationMap]
