---
name: SegmentBloodVesselsWithMultiScaleHessianBasedMeasure
---

# Segment Blood Vessels With Multi-Scale Hessian-Based Measure

```{index} single: MultiScaleHessianBasedMeasureImageFilter pair: segment; vessel pair: segment; tube
```

## Synopsis

Segment blood vessels with multi-scale Hessian-based measure.

## Results

:::{figure} Sidestream_dark_field_image.png
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
.. breathelink:: itk::MultiScaleHessianBasedMeasureImageFilter
```
