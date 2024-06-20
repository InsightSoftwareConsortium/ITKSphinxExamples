---
name: NormalizedCorrelationOfMaskedImage
---

# Normalized Correlation of Masked Image

```{index} single: NormalizedCorrelationImageFilter pair: correlation; masked
```

## Synopsis

Normalized correlation of a masked image.

## Results

:::{figure} mask.png
:alt: mask.png
:scale: 70%

mask.png
:::

:::{figure} image1.png
:alt: image1.png
:scale: 70%

image1.png
:::

:::{figure} image2.png
:alt: image2.png
:scale: 70%

image2.png
:::

:::{figure} NormalizedCorrelationOfMaskedImage.png
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
Maximum location fixed: [20, 6]
Maximum value: 1
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::NormalizedCorrelationImageFilter
```
