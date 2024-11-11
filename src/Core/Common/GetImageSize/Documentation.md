---
name: GetImageSize
---

# Get Image Size

```{index} single: Size pair: ImageRegion; IsInside
```

## Synopsis

Get the size of a itk::Image

## Results

:::{figure} Yinyang.png
:alt: Input yin-yang image.
:scale: 50%

Input Image
:::

Output::

: \[512, 342\]

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 17-
```

## Classes demonstrated

```{eval-rst}
.. breathelinkstruct:: itk::Size
```
