---
name: DeformAVolumeWithAThinPlateSpline
---

# Deform a Volume With a Thin Plate Spline

```{index} single: ThinPlateSplineKernelTransform
```

## Synopsis

This example deforms a 3D volume with the thin plate spline.

## Results

:::{figure} InputImage.png
:alt: Input image
:width: 640px

Input image
:::

:::{figure} DeformedImage.png
:alt: Deformed image
:width: 640px

Deformed image
:::

:::{figure} CheckerBoard.png
:alt: CheckerBoard image
:width: 640px

CheckerBoard image
:::

## Code

### Python

```{literalinclude} Code.py
:language: python
:lines: 1,16-
```

### C++

```{literalinclude} Code.cxx
:language: c++
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ThinPlateSplineKernelTransform
```
