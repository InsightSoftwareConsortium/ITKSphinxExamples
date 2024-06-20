---
name: DilateABinaryImage
substitutions:
  input: |-
    ```{image} Yinyang.png
    :alt: Input yin-yang image.
    :scale: 50%
    ```
  input_caption: Input binary image.
  output: |-
    ```{image} OutputBaseline.png
    :alt: Dilated output.
    :scale: 50%
    ```
  output_caption: Dilated output image.
---

# Dilate a Binary Image

```{index} single: BinaryBallStructuringElement single: BinaryDilateImageFilter pair: mathematical morphology; dilation pair: BinaryBallStructuringElement; SetRadius
```

:::{seealso}
dilation; erosion
:::

## Synopsis

Dilate regions by using a specified kernel, also known as a structuring element.
In this example, the white regions are enlarged.

## Results

```{eval-rst}
+-----------------+------------------+
|     |input|     |     |output|     |
+                 +                  +
| |input_caption| | |output_caption| |
+-----------------+------------------+
```

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
.. breathelink:: itk::BinaryDilateImageFilter itk::BinaryBallStructuringElement
```
