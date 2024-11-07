---
name: ApplyAFilterToASpecifiedRegionOfAnImage
---

# Apply a Filter to a Specified Region of an Image

```{index} single: DerivativeImageFilter pair: derivative; image
```

## Synopsis

Computes the derivative of an image in a particular direction.

## Results

:::{figure} BrainProtonDensitySlice.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} DerivativeImageQuickview.png
:alt: Output in QuickView
:scale: 50%

Output in QuickView
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::DerivativeImageFilter
```
