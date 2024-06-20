---
name: DilateAGrayscaleImage
---

# Dilate a grayscale image

```{index} single: FlatStructuringElement single: GrayscaleDilateImageFilter pair: mathematical morphology; dilation
```

:::{seealso}
dilation; erosion
:::

## Synopsis

Dilate regions by using a specified kernel, also known as a structuring element. In this example, the white regions are enlarged.

## Results

:::{figure} cthead1.png
:alt: Input ct head image.
:scale: 50%

Input grayscale image.
:::

:::{figure} OutputBaseline.png
:alt: Dilated output.
:scale: 50%

Dilated output.
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
.. breathelink:: itk::GrayscaleDilateImageFilter itk::FlatStructuringElement
```
