---
name: NormalizedCorrelationUsingFFT
---

# Normalized Correlation Using FFT

```{index} single: FFTNormalizedCorrelationImageFilter
```

## Synopsis

Normalized correlation using the FFT.

## Results

:::{figure} fixedImage.png
:alt: fixedImage.png
:scale: 70%

fixedImage.png
:::

:::{figure} movingImage.png
:alt: movingImage.png
:scale: 70%

movingImage.png
:::

:::{figure} NormalizedCorrelationUsingFFT.png
:alt: correlation.mha
:scale: 70%

correlation.mha
:::

:::{figure} correlation.png
:alt: correlation.png
:scale: 70%

correlation.png
:::

Output:

```
Maximum location: [45, 44]
Maximum location fixed: [5, 6]
Maximum value: 1
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::FFTNormalizedCorrelationImageFilter
```
