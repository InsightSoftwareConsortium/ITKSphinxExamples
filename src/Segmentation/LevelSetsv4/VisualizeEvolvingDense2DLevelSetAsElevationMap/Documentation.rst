:name: VisualizeEvolvingDense2DLevelSetAsElevationMap

Visualize an Evolving Dense 2D Level Set as Elevation Map
=========================================================

.. index::
   single: BinaryImageToLevelSetImageAdaptor
   single: SinRegularizedHeavisideStepFunction
   single: LevelSetDenseImage
   single: LevelSetContainer
   single: LevelSetEquationChanAndVeseInternalTerm
   single: LevelSetEquationChanAndVeseExternalTerm
   single: LevelSetEvolutionNumberOfIterationsStoppingCriterion
   single: LevelSetEvolution

Synopsis
--------

Evolve a dense level-set function with the Chan and Vese region terms and write
the final function values as an image. Rendered as a height field, these values
form an elevation map whose zero level is the evolved contour.


Results
-------

.. figure:: cells.png
  :scale: 100%
  :alt: Input image (cells)

  Input image


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::LevelSetEvolution
