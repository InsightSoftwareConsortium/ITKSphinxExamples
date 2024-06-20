---
name: WriteAnImage
---

# Write an Image

```{index} single: ImageFileWriter
```

## Synopsis

This example demonstrates how to write an itk::Image to a file. The file
type is determined by the extension of the specified filename.

## Results

:::{figure} WriteAnImage.png
:alt: test.png
:scale: 70%

test.png
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
.. breathelink:: itk::ImageFileWriter
```
