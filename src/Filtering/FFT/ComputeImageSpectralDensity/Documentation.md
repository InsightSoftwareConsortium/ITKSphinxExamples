---
name: ComputeImageSpectralDensity
---

# Compute Image Spectral Density

```{index} single: ComplexToModulusImageFilter single: FFTShiftImageFilter single: ForwardFFTImageFilter single: Fast Fourier Transform single: spectral density
```

## Synopsis

Compute the magnitude of an image's spectral components.

## Results

:::{figure} Input.png
:alt: Input image
:scale: 100%

Input image
:::

:::{figure} Output.png
:alt: Output image of spectral density.
:scale: 100%

Output image of spectral density.  The DC component is shifted to the center
of the image.
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ComplexToModulusImageFilter
```

```{eval-rst}
.. breathelink:: itk::FFTShiftImageFilter
```
