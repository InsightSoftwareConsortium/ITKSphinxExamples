---
name: DerivativeImage
---

# Compute Derivative

```{index} single: DerivativeImageFilter
```

## Synopsis

This filter computes a n-th Derivative of a scalar-valued image in a specified direction.

## Results

:::{figure} BrainProtonDensitySlice.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} Output.png
:alt: Output image
:scale: 50%

Output image
:::

:::{figure} Output_normalized.png
:alt: Output normalized image
:scale: 50%

Output normalized image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::DerivativeImageFilter
```
