---
name: UpsampleAnImage
---

# Upsample an Image

```{index} single: ResampleImageFilter single: LinearInterpolateImageFunction single: ScaleTransform single: BSplineInterpolateImageFunction single: Upsampling
```

## Synopsis

Upsample an image.

## Results

:::{figure} OutputBaseline.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} BrainProtonDensitySlice.png
:alt: Output image
:scale: 50%

Output image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ResampleImageFilter
```

```{eval-rst}
.. breathelink:: itk::BSplineInterpolateImageFunction
```
