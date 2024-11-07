---
name: ExtraLargestConnectComponentFromBinaryImage
---

# Extra Largest Connect Component From Binary Image

```{index} single: ConnectedComponentImageFilter pair: binary; image
```

## Synopsis

Extract the largest connected component from a Binary Image.

## Results

:::{figure} Yinyang.png
:alt: input image
:scale: 70%

Input image.
:::

:::{figure} ExtraLargestConnectComponentFromBinaryImage.png
:alt: VTK Window
:scale: 70%

Output In VTK Window
:::

Output:

```
Number of objects: 3
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::ConnectedComponentImageFilter
```
