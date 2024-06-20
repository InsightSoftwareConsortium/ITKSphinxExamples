---
name: FlipAnImageOverSpecifiedAxes
---

# Flip an Image Over Specified Axes

```{index} single: FlipImageFilter single: flip
```

## Synopsis

Flip an image over the specified axes.  Pixels are swapped over the given axis.

## Results

:::{figure} Yinyang.png
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
.. breathelink:: itk::FlipImageFilter
```
