---
name: ComputeCurvatureFlow
---

# Compute Curvature Flow

```{index} single: CurvatureFlowImageFilter
```

## Synopsis

Denoise an image using curvature driven flow.

## Results

:::{figure} BrainProtonDensitySlice.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} OutputBaseline.png
:alt: Output image
:scale: 50%

Output image
:::

## Code

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 16-
```

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::CurvatureFlowImageFilter
```
