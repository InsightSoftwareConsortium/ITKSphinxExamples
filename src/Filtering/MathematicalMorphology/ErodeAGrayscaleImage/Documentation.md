---
name: ErodeAGrayscaleImage
---

# Erode a Grayscale Image

```{index} single: FlatStructuringElement single: GrayscaleErodeImageFilter pair: mathematical morphology; erosion
```

:::{seealso}
erosion; dilation
:::

## Synopsis

Erode regions by using a specified kernel, also known as a structuring element. In this example, the white regions shrink.

## Results

:::{figure} cthead1.png
:alt: Input ct head image.
:scale: 50%

Input grayscale image.
:::

:::{figure} OutputBaseline.png
:alt: Eroded output.
:scale: 50%

Eroded output.
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
.. breathelink:: itk::GrayscaleErodeImageFilter itk::FlatStructuringElement
```
