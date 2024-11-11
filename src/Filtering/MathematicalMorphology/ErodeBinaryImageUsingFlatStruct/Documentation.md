---
name: ErodeBinaryImageUsingFlatStruct
---

# Erode Binary Image Using Flat Structure Element

```{index} single: FlatStructuringElement pair: binary; image
```

## Synopsis

Erode a binary image using a flat (box) structuring element.

## Results

:::{figure} Yinyang.png
:scale: 70%

Input image.
:::

:::{figure} ErodeBinaryImageUsingFlatStruct.png
:scale: 70%

Yinyang.png And Output.png When Radius = 7
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::FlatStructuringElement
```
