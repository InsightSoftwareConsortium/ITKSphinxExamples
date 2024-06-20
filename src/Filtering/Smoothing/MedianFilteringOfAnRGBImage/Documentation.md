---
name: MedianFilteringOfAnRGBImage
---

# Median Filtering of an RGB Image

```{index} single: MedianImageFilter single: smooth
```

## Synopsis

Apply median filtering on a RGB Image. The sorting of pixel is performed on their luminance.

## Results

:::{figure} GourdsRGB.png
:alt: Input image

Input image
:::

:::{figure} OutputBaseline.png
:alt: Output image

Output image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MedianImageFilter
```
