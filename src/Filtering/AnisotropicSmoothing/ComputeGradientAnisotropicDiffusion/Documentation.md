---
name: ComputeGradientAnisotropicDiffusion
---

# Compute Gradient Anisotropic Diffusion

```{index} single: GradientAnisotropicDiffusionImageFilter
```

## Synopsis

Perform anisotropic diffusion on an image.

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
.. breathelink:: itk::GradientAnisotropicDiffusionImageFilter
```
