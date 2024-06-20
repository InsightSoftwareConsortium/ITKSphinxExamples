---
name: NormalizedCorrelationUsingFFTWithMaskImages
---

# Normalized Correlation Using FFT With Mask Images for Input Images

```{index} single: MaskedFFTNormalizedCorrelationImageFilter pair: masked; input single: FFT
```

## Synopsis

Normalized correlation using the FFT with optional mask images for both input images.

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

:::{figure} NormalizedCorrelationUsingFFTWithMaskImages.png
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
.. breathelink:: itk::MaskedFFTNormalizedCorrelationImageFilter
```
