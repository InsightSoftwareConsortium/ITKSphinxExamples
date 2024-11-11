---
name: ComputePeronaMalikAnisotropicDiffusion
---

# Perona Malik Anisotropic Diffusion on Grayscale Image

```{index} single: GradientAnisotropicDiffusionImageFilter single: smooth
```

## Synopsis

Perona Malik Anisotropic Diffusion for scalar valued images.

## Results

:::{figure} ComputePeronaMalikAnisotropicDiffusionComparison.png
:alt: Anisotropic diffusion comparison.
:scale: 50%

Before anisotropic diffusion (left) and after anisotropic diffusion
(right).
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
