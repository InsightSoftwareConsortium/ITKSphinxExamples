---
name: VisualizeEvolvingDense2DLevelSetAsElevationMap
---

# Visualize an Evolving Dense 2D Level Set as Elevation Map

```{index} single: VTKVisualize2DLevelSetAsElevationMap single: BinaryImageToLevelSetImageAdaptor single: SinRegularizedHeavisideStepFunction single: LevelSetDenseImage single: LevelSetContainer single: LevelSetEquationChanAndVeseInternalTerm single: LevelSetEquationChanAndVeseExternalTerm single: LevelSetEvolutionNumberOfIterationsStoppingCriterion single: LevelSetEvolution single: LevelSetIterationUpdateCommand
```

## Synopsis

Visualize an evolving dense level-set function 2D rendered as an elevation map.

## Results

:::{figure} cells.png
:alt: Input image (cells)
:scale: 100%

Input image
:::

:::{figure} levelsets.*
:alt: Evolving level-sets rendered as an elevation map
:scale: 100%

Evolving level-sets
:::

:::{only} html
```{image} levelsets.gif
:alt: Evolving level-sets animation
:scale: 100%
```
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

% [breathelink:: itk::VTKVisualize2DLevelSetAsElevationMap]
