---
name: VisualizeEvolvingDense2DLevelSetZeroSet
---

# Visualize an Evolving Dense 2D Level-Set Zero-Set

```{index} single: VTKVisualizeImageLevelSetIsoValues single: BinaryImageToLevelSetImageAdaptor single: SinRegularizedHeavisideStepFunction single: LevelSetDenseImage single: LevelSetContainer single: LevelSetEquationChanAndVeseInternalTerm single: LevelSetEquationChanAndVeseExternalTerm single: LevelSetEvolutionNumberOfIterationsStoppingCriterion single: LevelSetEvolution single: LevelSetIterationUpdateCommand
```

## Synopsis

Visualize the evolving zero-set of a dense level-set function 2D rendered.

## Results

:::{figure} cells.png
:alt: Input image (cells)
:scale: 100%

Input image
:::

:::{figure} levelsets.*
:alt: Evolving level-sets
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

% [breathelink:: itk::VTKVisualizeImageLevelSetIsoValues]
