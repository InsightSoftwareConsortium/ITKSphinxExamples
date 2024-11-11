---
name: ComputeGradientMagnitudeRecursiveGaussian
---

# Compute Gradient Magnitude Recursive Gaussian of Grayscale Image

```{index} single: GradientMagnitudeRecursiveGaussianImageFilter, Gaussian, gradient
```

## Synopsis

Compute the gradient magnitude of the image after first smoothing with a Gaussian kernel.

## Results

:::{figure} Gourds.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} ComputeGradientMagnitudeRecursiveGaussianTestOutput.png
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
.. breathelink:: itk::GradientMagnitudeRecursiveGaussianImageFilter
```
