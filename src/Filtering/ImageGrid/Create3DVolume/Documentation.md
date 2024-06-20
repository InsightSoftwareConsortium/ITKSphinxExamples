---
name: Create3DVolume
---

# Create 3D Volume

```{index} single: TileImageFilter single: append single: tile single: concatenate
```

## Synopsis

This example reads in a series of 2D images and stacks them to create a 3D image.

## Results

:::{figure} Input.png
:alt: Input 2D images
:scale: 50%

Input 2D images
:::

:::{figure} Output.png
:alt: Output 3D image
:scale: 80%

Single output 3D image
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
.. breathelink:: itk::TileImageFilter
```
