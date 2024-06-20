---
name: ApplyAffineTransformFromHomogeneousMatrixAndResample
---

# Apply Affine Transform From Homogeneous Matrix and Resample

```{index} single: AffineTransform single: WindowedSincInterpolateImageFunction single: ResampleImageFilter
```

## Synopsis

Given one homogeneous matrix (here a 3x3 matrix), apply the corresponding
transform to a given image and resample using a
WindowedSincInterpolateImageFunction.

## Results

:::{figure} Gourds.png
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

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::AffineTransform
```

```{eval-rst}
.. breathelink:: itk::WindowedSincInterpolateImageFunction
```

```{eval-rst}
.. breathelink:: itk::ResampleImageFilter
```
