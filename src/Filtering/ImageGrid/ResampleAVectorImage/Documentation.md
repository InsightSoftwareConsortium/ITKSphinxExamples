---
name: ResampleAVectorImage
---

# Resample a Vector Image

```{index} single: ResampleImageFilter single: IdentityTransform single: LinearInterpolateImageFunction single: RGBPixel
```

## Synopsis

Linearly interpolate a vector image.

The Python wrapping for the LinearInterpolateImageFunction using vector images was added in ITK 4.7.0.

## Results

:::{figure} VisibleWomanHeadSlice.png
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
.. breathelink:: itk::ResampleImageFilter
```
