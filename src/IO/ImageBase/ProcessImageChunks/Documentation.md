---
name: ProcessImageChunks
---

# Process Image Chunks

```{index} single: ImageFileWriter
```

## Synopsis

Process an image in small chunks.

## Results

:::{figure} Gourds.png
:alt: Input image

Input image
:::

:::{figure} OutputBaseline.png
:alt: Output image

Output image
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

```{literalinclude} Code.py
:language: python
:lines: 1, 16-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MedianImageFilter
```

```{eval-rst}
.. breathelink:: itk::ImageFileWriter
```
