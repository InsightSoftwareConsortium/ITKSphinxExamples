---
name: ThinImage
---

# Thin Image

```{index} single: BinaryThinningImageFilter
```

## Synopsis

Skeletonix/thin an image.

## Results

:::{figure} Input.png
:alt: Input.png
:scale: 70%

input.png
:::

:::{figure} OutputBaseline.png
:alt: OutputBaseline.png
:scale: 70%

OutputBaseline.png
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
.. breathelink:: itk::BinaryThinningImageFilter
```
