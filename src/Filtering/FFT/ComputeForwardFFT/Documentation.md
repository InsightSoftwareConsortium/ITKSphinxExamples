---
name: ComputeForwardFFT
---

# Compute Forward FFT

```{index} single: ForwardFFTImageFilter single: ComplexToRealImageFilter single: ComplexToImaginaryImageFilter single: ComplexToModulusImageFilter single: RescaleIntensityImageFilter single: WrapPadImageFilter single: NumericTraits single: ImageFileReader single: ImageFileWriter
```

## Synopsis

Compute forward FFT of an image.

## Results

:::{figure} HeadMRVolume.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} Real.png
:alt: Real image
:scale: 50%

Output Real image
:::

:::{figure} Complex.png
:alt: Imaginary image
:scale: 50%

Output Imaginary image
:::

:::{figure} Modulus.png
:alt: Modulus image
:scale: 50%

Output Modulus image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ForwardFFTImageFilter
```

```{eval-rst}
.. breathelink:: itk::ComplexToRealImageFilter
```

```{eval-rst}
.. breathelink:: itk::ComplexToImaginaryImageFilter
```

```{eval-rst}
.. breathelink:: itk::ComplexToModulusImageFilter
```

```{eval-rst}
.. breathelink:: itk::WrapPadImageFilter
```

```{eval-rst}
.. breathelink:: itk::RescaleIntensityImageFilter
```
