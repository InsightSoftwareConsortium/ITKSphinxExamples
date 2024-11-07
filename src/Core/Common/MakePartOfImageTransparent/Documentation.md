---
name: MakePartOfImageTransparent
---

# Make Part of an Image Transparent

```{index} single: RGBAPixel single: transparency
```

## Synopsis

Demonstrates how to assign transparency to pixels in an image, then writing the result to a tif file for inspection and verification.

## Results

:::{figure} MakePartOfImageTransparent.png
:alt: test.tif
:scale: 70%

Output Image.
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::RGBAPixel
```
