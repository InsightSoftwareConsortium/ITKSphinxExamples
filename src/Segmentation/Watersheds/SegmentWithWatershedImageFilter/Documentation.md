---
name: SegmentWithWatershedImageFilter
---

# Watershed Image Filter

```{index} single: WatershedImageFilter
```

## Synopsis

This example illustrates how to segment an image using the watershed method.

## Results

:::{figure} BrainProtonDensitySlice.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} SegmentWithWatershedImageFilterTest02Baseline.png
:alt: Segmented image
:scale: 50%

Segmented image
:::

## Code

### C++

```{literalinclude} Code.cxx
:language: c++
:lines: 18-
```

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 16-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::WatershedImageFilter
```
