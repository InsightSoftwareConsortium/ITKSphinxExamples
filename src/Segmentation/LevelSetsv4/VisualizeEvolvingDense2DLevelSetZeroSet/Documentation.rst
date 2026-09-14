:name: VisualizeEvolvingDense2DLevelSetZeroSet

Visualize an Evolving Dense 2D Level-Set Zero-Set
=================================================

.. index::
   single: VTKVisualizeImageLevelSetIsoValues
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

Visualize the evolving zero-set of a dense level-set function 2D rendered.


Results
-------

.. figure:: cells.png
  :scale: 100%
  :alt: Input image (cells)

  Input image

.. figure:: levelsets.*
  :scale: 100%
  :alt: Evolving level-sets

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

.. [breathelink:: itk::VTKVisualizeImageLevelSetIsoValues]
