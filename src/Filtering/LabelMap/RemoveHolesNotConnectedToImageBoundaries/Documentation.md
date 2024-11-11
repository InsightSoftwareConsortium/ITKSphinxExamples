---
name: RemoveHolesNotConnectedToImageBoundaries
---

# Remove Holes Not Connected to Image Boundaries

```{index} single: BinaryFillholeImageFilter
```

## Synopsis

Remove holes in one binary image not connected to its boundary. In this case
the foreground value for the image is taken to be zero (black), and everything
is filled in within the black boundary.

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
.. breathelink:: itk::BinaryFillholeImageFilter
```
