---
name: SmoothImageWhilePreservingEdges2
---

# Smooth Image While Preserving Edges (Curvature)

```{index} single: VectorCurvatureAnisotropicDiffusionImageFilter single: curvature pair: smooth; image pair: preserve; edges
```

## Synopsis

Smooth an image while preserving edges.

## Results

:::{figure} Yinyang.png
:scale: 70%

Input image.
:::

:::{figure} SmoothImageWhilePreservingEdges2.png
:scale: 70%

Output In VTK Window
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::VectorCurvatureAnisotropicDiffusionImageFilter
```
