---
name: ErodeABinaryImage
substitutions:
  input: |-
    ```{image} Yinyang.png
    :alt: Input yin-yang image.
    :scale: 50%
    ```
  input_caption: Input binary image.
  output: |-
    ```{image} OutputBaseline.png
    :alt: Eroded output.
    :scale: 50%
    ```
  output_caption: Eroded output image.
---

# Erode a Binary Image

```{index} single: BinaryBallStructuringElement single: BinaryErodeImageFilter pair: mathematical morphology; erosion pair: BinaryBallStructuringElement; SetRadius
```

:::{seealso}
erosion; dilation
:::

## Synopsis

Erode regions by using a specified kernel, also known as a structuring element.  In this example, the white regions shrink.

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
.. breathelink:: itk::BinaryErodeImageFilter itk::BinaryBallStructuringElement
```
