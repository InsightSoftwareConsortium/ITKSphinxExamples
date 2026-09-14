:name: VisualizeEvolvingDense2DLevelSetZeroSet

Visualize an Evolving Dense 2D Level-Set Zero-Set
=================================================

.. index::
   single: BinaryImageToLevelSetImageAdaptor
   single: SinRegularizedHeavisideStepFunction
   single: LevelSetDenseImage
   single: LevelSetContainer
   single: LevelSetEquationChanAndVeseInternalTerm
   single: LevelSetEquationChanAndVeseExternalTerm
   single: LevelSetEvolutionNumberOfIterationsStoppingCriterion
   single: LevelSetEvolution
   single: ZeroCrossingImageFilter

Synopsis
--------

Evolve a dense level-set function with the Chan and Vese region terms, extract
the zero set of the result with itk::ZeroCrossingImageFilter, and write the
contour as an image.


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
